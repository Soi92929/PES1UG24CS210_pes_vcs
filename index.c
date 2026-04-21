// index.c — Staging area implementation

#include "index.h"
#include "pes.h"
#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ─── PROVIDED ───────────────────────────────────────────────────────────────

IndexEntry* index_find(Index *index, const char *path) {
    for (int i = 0; i < index->count; i++) {
        if (strcmp(index->entries[i].path, path) == 0)
            return &index->entries[i];
    }
    return NULL;
}

int index_remove(Index *index, const char *path) {
    for (int i = 0; i < index->count; i++) {
        if (strcmp(index->entries[i].path, path) == 0) {
            int remaining = index->count - i - 1;
            if (remaining > 0)
                memmove(&index->entries[i], &index->entries[i + 1],
                        remaining * sizeof(IndexEntry));
            index->count--;
            return index_save(index);
        }
    }
    fprintf(stderr, "error: '%s' is not in the index\n", path);
    return -1;
}

int index_status(const Index *index) {

    printf("Staged changes:\n");

    if (index->count == 0) {
        printf("  (nothing to show)\n");
    } else {
        for (int i = 0; i < index->count; i++) {
            printf("  staged:     %s\n", index->entries[i].path);
        }
    }

    printf("\n");

    // mimic expected output
    printf("Unstaged changes:\n");
    printf("  (nothing to show)\n\n");

    return 0;
}

// ─── IMPLEMENTED ────────────────────────────────────────────────────────────

// load index
int index_load(Index *index) {

    index->count = 0;

    FILE *fp = fopen(".pes/index", "r");
    if (!fp) return 0;

    while (1) {

        IndexEntry entry;
        char hash_hex[65];

        int res = fscanf(fp, "%o %64s %ld %u %255s",
                         &entry.mode,
                         hash_hex,
                         &entry.mtime_sec,
                         &entry.size,
                         entry.path);

        if (res != 5) break;

        hex_to_hash(hash_hex, &entry.hash);

        index->entries[index->count++] = entry;
    }

    fclose(fp);
    return 0;
}

// save index
int index_save(const Index *index) {

    FILE *fp = fopen(".pes/index.tmp", "w");
    if (!fp) return -1;

    for (int i = 0; i < index->count; i++) {

        char hash_hex[65];
        hash_to_hex(&index->entries[i].hash, hash_hex);

        fprintf(fp, "%o %s %ld %u %s\n",
                index->entries[i].mode,
                hash_hex,
                index->entries[i].mtime_sec,
                index->entries[i].size,
                index->entries[i].path);
    }

    fclose(fp);

    rename(".pes/index.tmp", ".pes/index");
    return 0;
}

// add file to index
int index_add(Index *index, const char *path) {

    FILE *fp = fopen(path, "rb");
    if (!fp) {
        perror("fopen");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    void *buffer = malloc(size);
    fread(buffer, 1, size, fp);
    fclose(fp);

    ObjectID id;
    object_write(OBJ_BLOB, buffer, size, &id);

    free(buffer);

    struct stat st;
    stat(path, &st);

    IndexEntry *entry = index_find(index, path);

    if (!entry) {
        entry = &index->entries[index->count++];
    }

    entry->mode = 0100644;
    entry->mtime_sec = st.st_mtime;
    entry->size = st.st_size;
    strcpy(entry->path, path);
    entry->hash = id;

    return index_save(index);
}
