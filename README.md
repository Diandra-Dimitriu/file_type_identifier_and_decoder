# Caesar Cipher Cryptanalysis & File Recovery

This repository contains the tools and methodology used to solve a cryptanalysis assignment. The objective was to take an encrypted binary file, determine the unknown Caesar cipher shift key, and identify the underlying file format to recover the original data.

## Assignment Context

We were provided with a uniquely encrypted file (e.g., `john_doe`) that had been obfuscated using a Caesar cipher. The specific shift key was completely unknown. 

The primary goals of the assignment were to:
1. **Decrypt the file** by determining the correct shift value.
2. **Identify the file type** from a predefined list of 16 possible formats: `3GP, AVI, BMP, JPG, EXE, XLS, XLSX, PPT, PPTX, DOC, DOCX, PDF, MP3, MP4, PNG, TAR.GZ` (12 unique hex file signatures).
3. **Analyze the recovered contents** to confirm the decryption was successful.



##  Methodology & Tools

To solve this, I developed two primary C programs (included in this repository):

### 1. The Brute-Force & Signature Detector (`security2.c`)
Since the cipher value was unknown, I wrote a program to automate the cryptanalysis. 
* **The Shift:** The program iterates through all 256 possible byte shifts (0-255).
* **The Verification:** For each shift, it decrypts the file in memory and inspects the first few bytes (file signatures).
* **The Match:** It cross-references these bytes against a hardcoded dictionary of hexadecimal signatures for the 16 target formats. When a match is found, the program halts and outputs the correct decryption key and file type.

### 2. The Cipher Utility (`security1.c`)
A command-line tool used to manually apply or reverse the Caesar cipher on binary files once the correct key is known.

## Findings & Results

Upon running the cryptanalysis tool against the provided encrypted file, the following results were achieved:

* **Decryption Key:** `9`
* **File Type:** `TAR.GZ`
* **Magic Number Match:** The tool successfully matched the decrypted header to `0x1F, 0x8B, 0x08`, the standard file signature for a GZIP compressed TAR archive.

### Analysis of Recovered Contents
After decrypting the file with a shift of 9 and extracting the resulting archive, the original contents were fully recovered. The archive contained the source code tree for a legacy open-source software project. 


## Compilation & Usage

To compile the tools using GCC:

```bash
gcc security1.c -o cipher_tool
gcc security2.c -o bruteforce_tool
```

To use the tools:
```bash
./security2.c encoded out
./security1.c -d encoded -o out -k key
