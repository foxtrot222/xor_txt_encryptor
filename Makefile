xor_encryptor: ./src/xor_encryptor.c
	gcc -Wall -o xor_encryptor ./src/xor_encryptor.c

clean:
	rm -rf xor_encryptor
