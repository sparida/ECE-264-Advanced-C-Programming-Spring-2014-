#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <libgen.h>
#include <string.h>
#include "answer05.h"

#define TRUE 1
#define FALSE 0

Image * Image_load(const char * filename)
{
ImageHeader header;
size_t read;
Image *tmp_im = NULL, *im = NULL;

FILE *fp = fopen(filename, "rb");
int err = fp == NULL;
if(err) fprintf(stderr, "Unable to open file %s!\n", filename);

if(!err)
{
read = fread(&header, sizeof(ImageHeader), 1, fp);

err = read != 1 ||
header.magic_number != ECE264_IMAGE_MAGIC_NUMBER ||
header.width == 0 ||
header.height == 0 ||
header.comment_len == 0;
if(err) fprintf(stderr, "Corrupt Header\n");
}

if(!err)
{
tmp_im = malloc(sizeof(Image));
err = tmp_im == NULL;
if(err) fprintf(stderr, "Unable to allocate memory for image\n");
}

if(!err)
{
tmp_im->width = header.width;
tmp_im->height = header.height;
tmp_im->comment = malloc(sizeof(char) * header.comment_len);
tmp_im->data = malloc(sizeof(char) * header.width * header.height);
err = tmp_im->comment == NULL || tmp_im->data == NULL;
if(err) fprintf(stderr, "Unable to allocate memory for comment or data\n");

}

if(!err)
{
read = fread(tmp_im->comment, sizeof(char), header.comment_len, fp);
err = read != header.comment_len ||
tmp_im->comment[header.comment_len - 1] != '\0';
if(err) fprintf(stderr, "Unable to read datat into allocated memory\n");
}

if(!err)
{
read = fread(tmp_im->data, sizeof(char), header.width * header.height, fp);
err = read != header.width * header.height;
if(err) fprintf(stderr, "Unable to read data into allocated image memory\n");
}

if(!err)
{
fgetc(fp);
err = !feof(fp);
if(err) fprintf(stderr, "EOF not Reached\n");
}

if(!err)
{
im = tmp_im; // bmp will be returned
tmp_im = NULL; // and not cleaned
}

if(tmp_im != NULL)
{
free(tmp_im->comment); // Remember, you can always free(NULL)
free(tmp_im->data);
free(tmp_im);
}

if(fp != NULL)
{
fclose(fp);
}

return im;

}

void linearNormalization(int width, int height, uint8_t * intensity)
{
	int i = 0;
	uint8_t  min = intensity[0], max = intensity[0];

	for(i = 0; i < (height * width); i++)
	{
		
			if(intensity[i] > max) max = intensity[i];
			if(intensity[i] < min) min = intensity[i];

	}

	for(i = 0; i < (height * width); i++)
	{
			intensity[i] = (intensity[i] - min) * 255.0 / (max - min);
	}
}

void Image_free(Image * image)
{
	if(image != NULL)
	{
		free(image->comment);
		free(image->data);
		free(image);
	}
}

int Image_save(const char * filename, Image * image)
{
    int err = FALSE; 
    FILE * fp = NULL; 
    size_t written = 0;

    // Attempt to open file for writing
    fp = fopen(filename, "wb");
    if(fp == NULL) {
	fprintf(stderr, "Failed to open '%s' for writing\n", filename);
	return FALSE; // No file ==> out of here.
    
    }


    // Prepare the header
    ImageHeader header;
    header.magic_number = ECE264_IMAGE_MAGIC_NUMBER;
    header.width = image->width;
    header.height = image->height;
    header.comment_len = strlen(image->comment) + 1;

  

    if(!err) {  // Write the header
	written = fwrite(&header, sizeof(ImageHeader), 1, fp);
	if(written != 1) {
	    fprintf(stderr, 
		    "Error: did not write correct header!\n");

	    err = TRUE;	
	}
    }



    if(!err)
    {
	    written = fwrite(image->comment, sizeof(char), (size_t) header.comment_len, fp);
	    if(written != (size_t) header.comment_len)
	    {
		    fprintf(stderr, "Unable to write image comment to file\n");
		    err = TRUE;
	    }
    }

    if(!err)
    {
	    written = fwrite(image->data, sizeof(uint8_t), (size_t) header.height * header.width, fp);
	    if(written != (size_t) header.height * header.width)
	    {
		    fprintf(stderr, "Unable to write image data comment to file\n");
		    err = TRUE;
	    }
    }
    
    if(fp) fclose(fp);

    return !err;
}
