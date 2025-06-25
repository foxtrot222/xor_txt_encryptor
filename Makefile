# SPDX-FileCopyrightText: 2025 Tirth Kavathiya <tirthkavathiya@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

xor_encryptor: ./src/xor_encryptor.c
	gcc -Wall -o xor_encryptor ./src/xor_encryptor.c

clean:
	rm -rf xor_encryptor
