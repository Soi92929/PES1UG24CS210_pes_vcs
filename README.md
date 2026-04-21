# 📦 PES Version Control System (PES VCS)

## 👨‍💻 Author

**Kabir Raju G**  
**SRN:** PES1UG24CS210  

---

## 📖 Overview

This project implements a simplified **Git-like Version Control System (PES VCS)** to understand how version control systems work internally.

It demonstrates:
- content-addressable storage using hashing  
- file staging using an index  
- directory representation using tree objects  
- commit creation and history tracking  

---

## 🧱 Repository Structure

```
.pes/
├── objects/        # Stores blob, tree, commit objects
├── refs/heads/     # Branch references
├── HEAD            # Points to current branch
├── index           # Staging area
```

---

## ⚙️ Features Implemented

### ✅ Phase 1 — Object Storage
- Stores file contents as **blob objects**
- Uses **SHA-256 hashing**
- Prevents duplicate storage

---

### ✅ Phase 2 — Tree Objects
- Builds directory structure using **tree objects**
- Converts staged files into hierarchical representation

---

### ✅ Phase 3 — Index (Staging Area)
- Implements staging via `.pes/index`
- Tracks metadata:
  - file mode  
  - hash  
  - timestamp  
  - size  
- Supports:
  - `pes add`
  - `pes status`

---

### ✅ Phase 4 — Commits & History
- Creates **commit objects**
- Links commits using parent references
- Maintains commit history
- Supports:
  - `pes commit`
  - `pes log`

---

## 🚀 How to Run

### Compile
```bash
make clean
make pes
```

### Initialize Repository
```bash
./pes init
```

### Add Files
```bash
echo "hello" > file1.txt
echo "world" > file2.txt

./pes add file1.txt file2.txt
```

### Commit Changes
```bash
./pes commit -m "Initial commit"
```

### View Status
```bash
./pes status
```

### View Commit History
```bash
./pes log
```

---

## 🧪 Testing

Integration testing was performed using:

```bash
make test-integration
```

### ✔ Verified:
- repository initialization  
- staging functionality  
- commit creation  
- history traversal  
- object storage correctness  

---

## 🧠 Key Concepts

- **Blob** → stores file content  
- **Tree** → represents directory structure  
- **Commit** → snapshot + metadata + parent  
- **Index** → staging area  

---

## 🔐 Design Highlights

- Content-addressable storage ensures integrity  
- Hash-based identification prevents duplication  
- Atomic writes prevent corruption  
- Linked commit history enables version tracking  

---

## 📸 Screenshots & Report

All required screenshots for:
- object storage  
- tree structure  
- index operations  
- commit history  
- integration test outputs  

are included in:

**SCREENSHOTS_REPORT_210.pdf**

---

## 🏁 Conclusion

This project demonstrates how a version control system works internally, including how files are stored, tracked, and versioned efficiently using object-based design and hashing.

---

## 🔗 Repository

https://github.com/Soi92929/PES1UG24CS210_pes_vcs
