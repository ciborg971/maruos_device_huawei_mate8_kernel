/*
 *************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *
 *  Version:    C, Version 2.1
 *
 *  File:       dhry_1.c (part 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 *************************************************************************
 */

#include "dhry.h"

/* This number does not matter. */
#define CLOCKS_PER_SEC 1000

/* Global Variables: */

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];

/* There was a bug here. The size of 'Reg_Define' was the length of
   the string "Register option selected.", but below the string
   "Register option not selected." is copied to 'Reg_Define', thus
   writing 4 bytes past the end of 'Reg_Define'. Fixed by declaring
   'Reg_Define' to be big enough to hold the longer string. */
char Reg_Define[32] = "Register option selected.";

/*
  forward declaration necessary since Enumeration may not simply be int
*/

#ifndef ROPT
#define REG
/* REG becomes defined as empty */
/* i.e. no register variables   */
#else
#define REG register
#endif


/* variables for time measurement: */

/* #define Too_Small_Time 2 */
#define Too_Small_Time 0

/* Measurements should last at least 2 seconds */
struct dhry_tms dhry_start_time, dhry_end_time;
double          User_Time = 0;
double          Microseconds = 0,
                Dhrystones_Per_Second,
                Vax_Mips;

/* end of variables for time measurement */

/**************************************************/
/* main program, corresponds to procedures        */
/* Main and Proc_0 in the Ada version             */
void dhry_times(struct dhry_tms *the_time)
{
    the_time->tms_utime = bsp_get_elapse_ms();
}
void Proc_2 (Int_Par_Ref)
     /*****************/
     /* executed once */
     /* *Int_Par_Ref == 1, becomes 4 */

     One_Fifty   *Int_Par_Ref;
{
  One_Fifty  Int_Loc;
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
      {
	Int_Loc -= 1;
	*Int_Par_Ref = Int_Loc - Int_Glob;
	Enum_Loc = Ident_1;
      } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void Proc_3 (Ptr_Ref_Par)
     /*****************/
     /* executed once */
     /* Ptr_Ref_Par becomes Ptr_Glob */

     Rec_Pointer *Ptr_Ref_Par;
{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */


void Proc_4 () /* without parameters */
     /*****************/
     /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = (Boolean)(Ch_1_Glob == 'A');
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */


void Proc_5 () /* without parameters */
     /*****************/
     /* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */

void Proc_1 (REG Rec_Pointer Ptr_Val_Par)
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;
  /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */

  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
  /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp
     == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
    {
      Next_Record->variant.var_1.Int_Comp = 6;
      Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp,
	      &Next_Record->variant.var_1.Enum_Comp);
      Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
      Proc_7 (Next_Record->variant.var_1.Int_Comp, 10,
	      &Next_Record->variant.var_1.Int_Comp);
    }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */


int dhry_main (int argc)
{
  One_Fifty       Int_1_Loc;
  REG   One_Fifty       Int_2_Loc;
  One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
  Enumeration     Enum_Loc;
  Str_30          Str_1_Loc;
  Str_30          Str_2_Loc;
  REG   int             Run_Index;
  REG   int             Number_Of_Runs = 0;

  /* Initializations */

  Next_Ptr_Glob = (Rec_Pointer) osl_malloc(sizeof (Rec_Type));
  Ptr_Glob = (Rec_Pointer) osl_malloc(sizeof (Rec_Type));

  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy_s (Ptr_Glob->variant.var_1.Str_Comp, sizeof(Ptr_Glob->variant.var_1.Str_Comp),
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy_s (Str_1_Loc, sizeof(Str_1_Loc), "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;

  /* Was missing in published program. Without this statement,    */
  /* Arr_2_Glob [8][7] would have an undefined value.             */
  /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
  /* overflow may occur for this array element.                   */

  dhry_printf("\n");
  dhry_printf("Dhrystone Benchmark, Version 2.1 (Language: C)\n");
  dhry_printf("\n");

  Number_Of_Runs = argc;

  if (Number_Of_Runs <= 0)
  {
	  dhry_printf("Please give the number[dhry_main(number)] of runs through the benchmark: ");
	  return 0;
/*
	  {
	    int n;
	    //scanf_s ("%d", &n);
	    Number_Of_Runs = n;
	  }
*/
  }

  dhry_printf("\n");

  dhry_printf("Execution starts, %d runs through Dhrystone\n",Number_Of_Runs);

  /***************/
  /* Start timer */
  /***************/

  dhry_times(&dhry_start_time);

  dhry_printf("BEGIN TIME: %d ms \n", dhry_start_time.tms_utime);


  for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
  {
      Proc_5();
      Proc_4();
      /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
      Int_1_Loc = 2;
      Int_2_Loc = 3;
      strcpy_s(Str_2_Loc, sizeof(Str_2_Loc), "DHRYSTONE PROGRAM, 2'ND STRING");
      Enum_Loc = Ident_2;
      Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
      /* Bool_Glob == 1 */
      while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
	{
	  Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
	  /* Int_3_Loc == 7 */
	  Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
	  /* Int_3_Loc == 7 */
	  Int_1_Loc += 1;
	} /* while */
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
      Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
      /* Int_Glob == 5 */
      Proc_1 (Ptr_Glob);
      for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
	/* loop body executed twice */
	{
	  if (Enum_Loc == Func_1 (Ch_Index, 'C'))
	    /* then, not executed */
	    {
	      Proc_6 (Ident_1, &Enum_Loc);
	      strcpy_s (Str_2_Loc, sizeof(Str_2_Loc), "DHRYSTONE PROGRAM, 3'RD STRING");
	      Int_2_Loc = Run_Index;
	      Int_Glob = Run_Index;
	    }
	}
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
      Int_2_Loc = Int_2_Loc * Int_1_Loc;
      Int_1_Loc = Int_2_Loc / Int_3_Loc;
      Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
      /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
      Proc_2 (&Int_1_Loc);
      /* Int_1_Loc == 5 */

    } /* loop "for Run_Index" */

  /**************/
  /* Stop timer */
  /**************/

  dhry_times(&dhry_end_time);
  dhry_printf("END TIME: %d ms \n", dhry_end_time.tms_utime);

  User_Time = (double)(dhry_end_time.tms_utime - dhry_start_time.tms_utime);
  dhry_printf("USER TIME (END-START) in Clock Cycles : %lf\n", User_Time);

  if (User_Time < Too_Small_Time)
    {
      dhry_printf("Measured time too small to obtain meaningful results\n");
      dhry_printf("Please increase number of runs\n");
      dhry_printf("\n");
    }
  else
    {
      /* CLOCKS_PER_SEC defined in <machine/time.h> -- define __XTENSA__ */
      Microseconds = User_Time / ((double)CLOCKS_PER_SEC * (double) Number_Of_Runs);
      dhry_printf("MICROSEC PER RUN: %lf \n", Microseconds);
      Dhrystones_Per_Second = (double) (1/Microseconds);
      Vax_Mips = Dhrystones_Per_Second / 1757.0;

#ifdef ROPT
      dhry_printf("Register option selected?  YES\n");
#else
      dhry_printf("Register option selected?  NO\n");
      strcpy_s(Reg_Define, sizeof(Reg_Define), "Register option not selected.");
#endif
      dhry_printf("Microseconds for one run through Dhrystone: ");
      dhry_printf("%lf \n", Microseconds);
      dhry_printf("Dhrystones per Second:                      ");
      dhry_printf("%lf \n", Dhrystones_Per_Second);
      dhry_printf("VAX MIPS rating = %lf \n",Vax_Mips);
      dhry_printf("DMIPS/MHz is %lf \n",Vax_Mips * 1000000 /CLOCKS_PER_SEC);
      dhry_printf("\n");
    }
  return 0;
}

/* Procedure for the assignment of structures,          */
/* if the C compiler doesn't support this feature       */
#ifdef  NOSTRUCTASSIGN
memcpy (d, s, l)
     register char   *d;
     register char   *s;
     register int    l;
{
  while (l--) *d++ = *s++;
}
#endif

