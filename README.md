<img src="ih8pdf.png"  width="150" />

-----
I HATE PDF. A fast and basic way to compress PDFs. It quickly compresses PDF files using [Ghostscript](https://ghostscript.com/). It can compress multiple files at once. The compressed output files are automatically named by prefixing **`compressed_`** to the original filename. 

## Usage

**General Syntax**:

```bash
ih8pdf [OPTIONS] <file1.pdf> [file2.pdf ...]
```

**Options**:

- `-c <level>` sets the compression level:
    - **0** → `/prepress` (high quality, bigger file)
    - **1** → `/ebook` (medium quality) — _default_
    - **2** → `/screen` (lowest quality, smallest file size) 

## Requirements

- [Ghostscript](https://ghostscript.com/) 
- A C compiler
## Installation Using the Makefile

1. **Clone** the repository:

```bash
git clone https://github.com/YourUsername/ih8pdf.git
cd ih8pdf
    ```

2. **Compile**:

    ```bash
make
    ```

3. **Install** to `/usr/local/bin`:

    ```bash
sudo make install
make clean
    ```

4. **Uninstall** 

    ```bash
sudo make uninstall
    ```

### Examples

1. **Compress a Single PDF File**

    ```bash
ih8pdf file1.pdf
    ```
Output => compressed_file1.pdf
1. **Specify a Compression Level**

    ```bash
    ih8pdf -c 1 file1.pdf
    ```
Uses compression level 1 (/ebook) => compressed_file1.pdf

1. **Compress Multiple Files**:

    ```bash
    ih8pdf file1.pdf file2.pdf
    ```
 Output => compressed_file1.pdf, compressed_file2.pdf

