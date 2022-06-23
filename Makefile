all: driver test
	
driver: outputfolder
	gcc -g Marcher.c ImgUtils.c Driver.c -o Marcher -lm

test: outputfolder
	gcc -g Marcher.c ImgUtils.c TestMarcher.c -o TestMarcher -lm

run: test
	./TestMarcher

outputfolder:
	mkdir -p output

clean:
	rm -f Marcher TestMarcher
