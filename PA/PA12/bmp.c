#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "bmp.h"

#define SUCCESS 0
#define FAILURE -1

/* a region as the indexes for the pixels */
typedef struct 
{
	int index1; /* inclusive */
	int index2; /* inclusive */
	char * data;
} Region;

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
  {
    return NULL;
  }
  return image;

}

void BMP_destroy(BMP_Image *image)
{    
    // deallocate the allocated memory
  free(image->data);
  free(image);
}

BMP_Image *BMP_load(const char *filename)
{
    // FILL IN CODE HERE!
  FILE *f = fopen(filename, "rb");
  if(f == NULL)
  {
    return NULL;
  }
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
  {
    return NULL;
  }
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

void * invert_Region(void * reg){
  int i;
  Region *region = (Region *) reg;
  for(i=region->index1; i<= region->index2; i++)
  {
    region->data[i] = 255 - region->data[i];
  }
	// loop through each byte in the image data region
	// replace each byte "value" the image data with "255 - value"

  pthread_exit(SUCCESS);	
	//exit the thread with with a return value of SUCCESS)
  return SUCCESS;
}

void BMP_invert(BMP_Image *image, int numThread)
{
  int i;
  int lastindex = 0;
  pthread_t *threads = malloc(numThread * sizeof(pthread_t));
  Region *regions = malloc(numThread * sizeof(Region));
  long *status = malloc(numThread * sizeof(long));
  
	// loop through the number of threads the program will spawn
  for(i=0; i<numThread; i++)
  {
		//Calculate the starting and ending indices for the data region
		//the thread will be inverting
  regions[i].index1 = lastindex;
  lastindex += image->data_size / numThread;
  regions[i].index2 = lastindex;
  lastindex++;
		//Store the location of the image data into the data region
  regions[i].data = image->data;
		//Initialize the attributes for the thread
  }
	//Make sure the ending index of the last thread is within the bounds 
	//of the image data
  regions[numThread - 1].index2 = image->data_size - 1;

	// loop through the number of threads the program will spawn
  for(i=0; i<numThread; i++)
  {
		//Print the starting and ending indicies of the data region for 
		//the thread
		//Create the thread 
  pthread_create(&threads[i], NULL, invert_Region, (void *) &regions[i]);
	// loop through the number of threads the program will spawn
  }
  		
		//Wait for all of the threads to finish executing
  for(i=0; i<numThread; i++)
  {
    pthread_join(threads[i], (void *) &(status[i]));
  }
	

  free(threads);
  free(regions);
  free(status);
}

int BMP_save(BMP_Image *image, const char *filename)
{
  FILE *f = fopen(filename, "wb");
  if(f == NULL)
  {
    return 0;
  }
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
    if (header->type != 0x4d42) return 0;

    // Make sure we are getting 24 bits per pixel
    if (header->bits != 24) return 0;

    // Make sure there is only one image plane
    if (header->planes != 1) return 0;

    // Make sure there is no compression
    if (header->compression != 0) return 0;

    return 1;
}

void BMP_printHeader(BMP_Header *header)
{
    printf("file type (should be 0x4d42): %x\n", header->type);
    printf("file size: %d\n", header->size);
    printf("offset to image data: %d\n", header->offset);
    printf("header size: %d\n", header->header_size);
    printf("width: %d\n", header->width);
    printf("height: %d\n", header->height);
    printf("planes: %d\n", header->planes);
    printf("bits: %d\n", header->bits);
}
