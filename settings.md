# 🛠️ Geany Useful Commands and Settings (Ubuntu)

A handy reference for managing files, compiling, and running tests efficiently when working with C++ in **Geany** on **Ubuntu**.

---

## 🧹 Clean Up

### 🔸 Delete Executables in the Current Directory
```bash
find . -maxdepth 1 -type f -executable -exec rm -f {} \;
```

### 🔸 Find All Executable Files (Current Directory + Subdirectories)
```bash
find . -type f -executable
```

### 🔸 Delete All Executable Files (Current Directory + Subdirectories)
```bash
find . -type f -executable -delete
```

---

## 📂 Test Input/Output Management

### 📅 Generate a `.in` File for Testing  
> You will need to rename the generated file properly afterward.
```bash
"./%e" > "%e".in
```

### 🧪 Execute All Tests
```bash
for x in "./%e"*.in ; do
    echo "$(basename "$x")"
    "./%e" < "$x"
    echo "=========================="
done
```

### 🧪 Execute All Tests and Save Output in a File (Overwrites the File)
```bash
> "%e".out
for x in "./%e"*.in ; do
    echo "$(basename "$x")"  >> "%e".out
    "./%e" < "$x" >> "%e".out 2>&1
    echo "==========================" >> "%e".out
done
```

### 🧂 Compare Two Output Files  
> No output means the files are equal.
```bash
diff file_name.out file_name2.out
```

---

## ⚙️ Compilation

### Compile with Warnings
```bash
g++ -std=gnu++11 -g -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -c "%f"
```

---

## 📁 File Finder Utilities

### Find All `.in` Files (Current Directory + Subdirectories)
```bash
find . -type f -name "*.in"
```

### Delete All `.in` Files
```bash
find . -type f -name "*.in" -delete
```

### Find All `.out` Files
```bash
find . -type f -name "*.out"
```

---

👉 **Tip:** You can add this file to your project root or your home directory for quick access anytime!

