# XOR TXT Encryptor
A simple command-line tool for encrypting and decrypting text files using XOR-based symmetric encryption.

## Usage

```bash
./xor_encryptor <input_file> <mode>
```

### Modes:

| Mode  | Description                                |
| ----- | ------------------------------------------ |
| `-er` | Encrypt file with a randomly generated key |
| `-ek` | Encrypt file with a key you provide        |
| `-d`  | Decrypt file with a key you provide        |
| `-v`  | View decrypted content in terminal         |

### Notes

* This uses XOR encryption — **not secure** for real-world data protection.
* `output.txt` will be **overwritten** without warning.
* Only works with **text files** (not binary-safe).
