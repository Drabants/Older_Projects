# huffpuff
Compression and Decompression for text

This is my solution for a assignment I was given for compressing and decompressing a file.
It uses a heap to construct a huffman tree based off how many times each character appears in the text given.
Once the huffman tree is constructed, it then produces a compressed file called "filename".huff.
This .huff file can then be fed into the puff executable. 
Puff will construct a symbol table, huffmantree, and the original message/text.
If the tree constructed from the symbol table is incorrect, the program will exit. 

This program was able to compress the fall of the house of usher from 61kb to 35kb bringing its space savings to about 42%....
