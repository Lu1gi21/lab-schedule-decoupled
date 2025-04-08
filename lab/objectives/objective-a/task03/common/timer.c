#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "timer.h"

#define ERROR_THRESHOLD 1e-4


extern void COMPUTE_NAME_TST( int m0, int n0,
			      float *input_x,
			      float *output_y );

extern double COMPUTE_FLOP_NAME_TST( int m0, int n0 );
extern double COMPUTE_BYTES_NAME_TST( int m0, int n0 );




void fill_buffer_with_random( int num_elems, float *buff )
{
  long long range = RAND_MAX;
  //long long range = 1000;
  
  for(int i = 0; i < num_elems; ++i)
    {
      buff[i] = ((float)(rand()-((range)/2)))/((float)range);
    }
}

void fill_buffer_with_value( int num_elems, float val, float *buff )
{
  for(int i = 0; i < num_elems; ++i)
    buff[i] = val;
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


int scale_p_on_pos_ret_v_on_neg(int p, int v)
{
  if (v < 1)
    return -1*v;
  else
    return v*p;
}

long pick_min_in_list(int num_trials, long *results)
{
  long current_min = LONG_MAX;

  for( int i = 0; i < num_trials; ++i )
    if( results[i] < current_min )
      current_min = results[i];

  return current_min;
}

void flush_cache()
{
  
  int size = 1024*1024*8;

  int *buff = (int *)malloc(sizeof(int)*size);
  int i, result = 0;
  volatile int sink;
  for (i = 0; i < size; i ++)
    result += buff[i];
  sink = result; /* So the compiler doesn't optimize away the loop */

  free(buff);
}

void time_function_under_test(int num_trials,
			      int num_runs_per_trial,
			      long *results, // results from each trial
			      int m0, int n0,
			      float *input,
			      float *output
			      )
{
  // Initialize the start and stop variables.
  TIMER_INIT_COUNTERS(stop, start);

  // Click the timer a few times so the subsequent measurements are more accurate
  TIMER_WARMUP(stop,start);

  // flush the cache
  flush_cache();
  
  for(int trial = 0; trial < num_trials; ++trial )
    {

	/*
	  Time code.
	*/
        // start timer
      TIMER_GET_CLOCK(start);

	////////////////////////
        // Benchmark the code //
	////////////////////////

	for(int runs = 0; runs < num_runs_per_trial; ++runs )
	  {
	    COMPUTE_NAME_TST( m0, n0,
			      input,
			      output );

	  }

	////////////////////////
        // End Benchmark      //
	////////////////////////

        
        // stop timer
	TIMER_GET_CLOCK(stop);

	// subtract the start time from the stop time
	TIMER_GET_DIFF(start,stop,results[trial])

    }

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

  int num_trials = 10;
  int num_runs_per_trial = 10;

  // Get command line arguments
  if(argc == 1 )
    {
      min_size  = 16;
      max_size  = 1024;
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
      //        argv 0   1    2    3  4  5          6
      printf("usage: %s min max step m0 n0 [filename]\n",
	     argv[0]);
      exit(1);
    }

  // print the first line of the output
  fprintf(result_file, "size,m,n,flop,throughput,bytes,GB_per_s,nanoseconds\n");

  
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

      // fill src_ref with random values
      fill_buffer_with_random( input_sz, input_ref );
      fill_buffer_with_value( output_sz, -1, output_ref );

     
      // copy src_ref to src_tst
      memcpy(input_tst,input_ref,input_sz*sizeof(float));
      memcpy(output_tst,output_ref,output_sz*sizeof(float));

      // Perform the computation
      long *results = (long *)malloc(sizeof(long)*num_trials);

      time_function_under_test(num_trials,
			       num_runs_per_trial,
			       results, // results from each trial
			       m0, n0,
			       input_tst,
			       output_tst
			       );

      long min_res = pick_min_in_list(num_trials, results);

      float nanoseconds = ((float)min_res)/(num_runs_per_trial);

      // This gives us throughput as GFLOP/s
      double flop   =  COMPUTE_FLOP_NAME_TST( m0, n0 );
      double throughput   =  flop / nanoseconds;
      double bytes        =  COMPUTE_BYTES_NAME_TST( m0, n0 );
      double gbytes_per_s =  COMPUTE_BYTES_NAME_TST( m0, n0 )/ nanoseconds;

      free(results);

      fprintf(result_file,
	      "%i,%i,%i,"
	      "%2.3e,%2.3e,"
	      "%2.3e,%2.3e,"
	      "%2.3e\n",
      	      m0,m0,n0,
	      flop, throughput,
	      bytes, gbytes_per_s,
	      nanoseconds);


      
      // Free the  buffers
      free(input_ref);
      free(output_ref);
      free(input_tst);
      free(output_tst);

    }


  // close the result file
  fclose(result_file);


}
