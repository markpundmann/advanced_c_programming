#include <stdlib.h>
#include <stdio.h>

#include "bmp.h"
#define BMP_HEADER_TYPE 0x4d42
#define BMP_HEADER_BITS 24
#define BMP_HEADER_PLANE 1

/*
 * 	You cannot use any "mysterious constants" below.
 * 	You need to define symbols above and use the symbols.
 * 	0 or 1 below are acceptable.
 */

BMP_Image *BMP_create(BMP_Header *header)
{
    // allocate memory for the image structure
    // copy the header
    // image size is file size minus the size of the header
    // allocate memory for the data
    // return the image structure
  BMP_Image *image = malloc(sizeof(BMP_Image));
  image->header = *header;
  image->width = header->width;
  image->height = header->height;
  image->bytes_per_pixel = header->bits/8;
  image->data_size = header->size - sizeof(BMP_Header);
  image->data = malloc(sizeof(char) * image-> data_size);
  if(image->data == NULL)
    return NULL;
  return image;
 
}

void BMP_destroy(BMP_Image *image)
{
    // FILL IN CODE HERE!
  free(image->data);
  free(image);
    // deallocate the allocated memory
}

BMP_Image *BMP_load(const char *filename)
{
    // read the header from the file
  FILE *f = fopen(filename, "rb");
  if(f == NULL)
    return NULL;
  BMP_Header header;
  if(fread(&header, sizeof(BMP_Header), 1, f) != 1)
  {
    fclose(f);
    return NULL;
  }
    // print the header information (use BMP_printHeader)
 BMP_printHeader(&header); 
    // make sure the header is valid before proceeding (use BMP_checkValid)
  if(!BMP_checkValid(&header))
    return NULL;
    // create the image structure (BMP_create)
  BMP_Image *image = BMP_create(&header);
    // read all of the image data
  if(fread(image->data, sizeof(char), image->data_size, f) != image->data_size)
  {
    fclose(f);
    BMP_destroy(image);
    return NULL;
  }
    // return the image

  return image; 
}

void BMP_invert(BMP_Image *image)
{
    // FILL IN CODE HERE!
  int index;
  for(index=0; index<image->data_size; index++)
  {
    image->data[index] = 255-image->data[index];
  }
    // loop through each byte in the image data
    // replace each byte "value" the image data with "255 - value"
}

int BMP_save(BMP_Image *image, const char *filename)
{
    // FILL IN CODE HERE!
  FILE *f = fopen(filename, "wb");
  if(f == NULL)
    return 0;

  if(fwrite(&(image->header), sizeof(BMP_Header), 1, f) != 1)
  {
    fclose(f);
    return 0;
  }
    // write the BMP header

    // write the image data
  if(fwrite(image->data, sizeof(char), image->data_size, f) != image->data_size)
  {
    fclose(f);
    return 0;
  }
  fclose(f);
  return 1;
}

// == DO NOT MODIFY ANYTHING BELOW THIS POINT ==============

int BMP_checkValid(BMP_Header *header)
{
    // Make sure this is a BMP file
    if (header->type != BMP_HEADER_TYPE) return 0;

    // Make sure we are getting 24 bits per pixel
    if (header->bits != BMP_HEADER_BITS) return 0;

    // Make sure there is only one image plane
    if (header->planes != BMP_HEADER_PLANE) return 0;

    // Make sure there is no compression
    if (header->compression != 0) return 0;

    return 1;
}

void BMP_printHeader(BMP_Header *header)
{
    printf("file type (should be %x): %x\n", BMP_HEADER_TYPE, header->type);
    printf("file size: %d\n", header->size);
    printf("offset to image data: %d\n", header->offset);
    printf("header size: %d\n", header->header_size);
    printf("width: %d\n", header->width);
    printf("height: %d\n", header->height);
    printf("planes: %d\n", header->planes);
    printf("bits: %d\n", header->bits);
}
