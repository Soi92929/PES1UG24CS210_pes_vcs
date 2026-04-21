📦 PES Version Control System (PES VCS)
👨‍💻 Author

Kabir Raju G
SRN: PES1UG24CS210

📖 Overview

This project implements a simplified Git-like Version Control System (PES VCS) to understand how real version control systems work internally.

The system supports:

storing files as hashed objects
staging using an index
building directory trees
creating commits with history
traversing commit logs
🧱 Repository Structure
.pes/
├── objects/        # Blob, tree, commit objects (content-addressable storage)
├── refs/heads/     # Branch references
├── HEAD            # Points to current branch
├── index           # Staging area
⚙️ Features Implemented
✅ Phase 1 — Object Storage
Stores file contents as blob objects
Uses SHA-256 hashing
Prevents duplicate storage
Verified using object tests and integration tests
✅ Phase 2 — Tree Objects
Builds directory structure using tree objects
Converts staged files (index) into hierarchical representation
Verified using xxd inspection and tree tests
✅ Phase 3 — Index (Staging Area)
Implements staging via .pes/index
Tracks metadata:
file mode
hash
timestamp
size
Supports:
pes add
pes status
✅ Phase 4 — Commits & History
Creates commit objects
Links commits via parent references
Maintains history traversal
Supports:
pes commit
pes log
🚀 How to Run
🔹 Compile
make clean
make pes
🔹 Initialize Repository
./pes init
🔹 Add Files
echo "hello" > file1.txt
echo "world" > file2.txt

./pes add file1.txt file2.txt
🔹 Commit Changes
./pes commit -m "Initial commit"
🔹 View Status
./pes status
🔹 View Commit History
./pes log
🧪 Testing

Integration testing was performed using:

make test-integration
✔ Verified:
repository initialization
staging functionality
commit creation
history traversal
object storage correctness
🧠 Key Concepts
Component	Description
Blob	Stores file content
Tree	Represents directory structure
Commit	Snapshot + metadata + parent
Index	Staging area before commit
🔐 Design Highlights
Content-addressable storage ensures data integrity
Hash-based identification prevents duplication
Atomic writes avoid corruption
Linked commits maintain history
📸 Screenshots & Report

All required screenshots for:

object storage
tree structure
index operations
commit history
integration test outputs

📄 are included in:

SCREENSHOTS_REPORT_210.pdf
🏁 Conclusion

This project demonstrates the internal workings of a version control system, including how data is stored, tracked, and versioned efficiently using object-based design and hashing.
