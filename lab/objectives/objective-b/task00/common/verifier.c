#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define ERROR_THRESHOLD 1e-3
#define HALF_RANGE 1000


extern void COMPUTE_NAME_REF( int m0, int n0,
			      float *input_x,
			      float *output_y );

extern void COMPUTE_NAME_TST( int m0, int n0,
			      float *input_x,
			      float *output_y );

void fill_buffer_with_random( int num_elems, float *buff )
{
  //long long range = RAND_MAX;  
  int upper = HALF_RANGE;
  int lower = -(HALF_RANGE);
  int range = upper - lower;
  
  for(int i = 0; i < num_elems; ++i)
    {
      //buff[i] = ((float)(rand()-((range)/2)))/((float)range);
      int rval = rand();
      int bounded_val = rval%(range+1)+lower;
      float scaled  = ((float)bounded_val)/((float)range);
      buff[i] = scaled;
    }
}

void fill_buffer_with_value( int num_elems, float val, float *buff )
{
  for(int i = 0; i < num_elems; ++i)
    buff[i] = val;
}


long count_num_errors(int m, int n, int rs, int cs, float *a)
{
  long counts = 0;

  for(int i = 0; i < m; ++i)
    for(int j = 0; j < n; ++j)
      {

	if(a[i*rs+j*cs]>ERROR_THRESHOLD)
	  counts++;
      }

  return counts;

}

float compute_pair_wise_diff(int m, int n, int rs, int cs, float *a, float *b, float *c)
{
  float max_diff = 0.0;

  for(int i = 0; i < m; ++i)
    for(int j = 0; j < n; ++j)
      {
	
	float sum  = fabs(a[i*rs+j*cs]+b[i*rs+j*cs]);
	float diff = fabs(a[i*rs+j*cs]-b[i*rs+j*cs]);

	float res = 0.0f;

	if(fabs(sum) < ERROR_THRESHOLD)
	  res = fabs(diff);
	else
	  res = 2*diff/sum;

	/*
	if(res > ERROR_THRESHOLD)
	  printf("%i, %f %f %f %f %f \n",i, a[i*rs+j*cs],b[i*rs+j*cs],sum,diff,res);
	*/

	c[i*rs+j*cs] = res;
	
	if( res > max_diff )
	  max_diff = res;

      }

  return max_diff;
}


float max_pair_wise_diff(int m, int n, int rs, int cs, float *a, float *b)
{
  float max_diff = 0.0;

  for(int i = 0; i < m; ++i)
    for(int j = 0; j < n; ++j)
      {
	float sum  = fabs(a[i*rs+j*cs]+b[i*rs+j*cs]);
	float diff = fabs(a[i*rs+j*cs]-b[i*rs+j*cs]);

	float res = 0.0f;

	if(sum == 0.0f)
	  res = diff;
	else
	  res = 2*diff/sum;

	if( res > max_diff )
	  max_diff = res;
      }

  return max_diff;
}

void print_vector( int m, float *x )
{
  for(int i = 0; i <m; ++i)
    printf("%f\n",x[i]);
}


int scale_p_on_pos_ret_v_on_neg(int p, int v)
{
  if (v < 1)
    return -1*v;
  else
    return v*p;
}


int main( int argc, char *argv[] )
{
  // What we will output to
  FILE *result_file;
  
  // Problem parameters
  int min_size;
  int max_size;
  int step_size;

  int in_m0;
  int in_n0;

  // Get command line arguments
  if(argc == 1 )
    {
      min_size  = 16;
      max_size  = 256;
      step_size = 16;

      // defaults
      in_m0=1;
      in_n0=1;

      // default to printing to stdout
      result_file = stdout;
    }
  else if(argc == 5 + 1 || argc == 6 + 1 )
    {
      min_size  = atoi(argv[1]);
      max_size  = atoi(argv[2]);
      step_size = atoi(argv[3]);

      in_m0=atoi(argv[4]);
      in_n0=atoi(argv[5]);

      // default to printing to stdout
      result_file = stdout;

      // If we were given a file, use that.
      if(argc == 6 + 1)
	result_file = fopen(argv[6],"w");

    }
  else
    {
      //      argv    0   1   2    3  4  5         6
      printf("usage: %s min max step m0 n0 [filename]\n",
	     argv[0]);
      exit(1);
    }
  
  bool wrote_header = false;

  // step through all of the problem sizes of interest
  for( int p = min_size;
       p < max_size;
       p += step_size )
    {

      // input sizes
      int m0=scale_p_on_pos_ret_v_on_neg(p,in_m0);
      int n0=scale_p_on_pos_ret_v_on_neg(p,in_n0);

      // How big of a buffer do we need
      int input_sz   = m0*n0;
      int output_sz  = m0*n0;

      float *input_ref   = (float *)malloc(sizeof(float)*input_sz);
      float *output_ref  = (float *)malloc(sizeof(float)*output_sz);

      float *input_tst   = (float *)malloc(sizeof(float)*input_sz);
      float *output_tst  = (float *)malloc(sizeof(float)*output_sz);
      float *output_diffs = (float *)malloc(sizeof(float)*output_sz);

      // fill src_ref with random values
      fill_buffer_with_random( input_sz, input_ref );
      //fill_buffer_with_value( input_sz, 1.0f, input_ref );
      fill_buffer_with_value( output_sz, 0.0f, output_ref );

     
      // copy src_ref to src_tst
      memcpy(input_tst,input_ref,input_sz*sizeof(float));
      memcpy(output_tst,output_ref,output_sz*sizeof(float));

      /*
	Run the reference
      */
     
      // Perform the computation
      COMPUTE_NAME_REF( m0, n0,
			input_ref,
			output_ref );



      // run the test
      // Perform the computation
      COMPUTE_NAME_TST( m0, n0,
			input_tst,
			output_tst );


      // compute the error
      float res = compute_pair_wise_diff(output_sz,1,1,1, output_ref, output_tst, output_diffs);
      long counts = count_num_errors(output_sz,1,1,1, output_diffs);

      if (!wrote_header) {
          fprintf(result_file, "m,n,error,status\n");
          wrote_header = true;
      }

      fprintf(result_file, "%i, %li, %f, ",
	      m0, counts, res);
      
      // if our error is greater than some threshold
      if( res > ERROR_THRESHOLD )
	fprintf(result_file, "FAIL\n");
      else
	fprintf(result_file, "PASS\n");

      // Free the  buffers
      free(input_ref);
      free(output_ref);
      free(input_tst);
      free(output_tst);
      free(output_diffs);

    }


  // close the result file
  fclose(result_file);


}
