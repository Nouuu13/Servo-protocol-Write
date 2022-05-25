#define soc_cv_av

#define DEBUG

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "hwlib.h"
#include "soc_cv_av/socal/socal.h"
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "hps_0.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 ) //64 MB with 32 bit adress space this is 256 MB
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )


//setting for the HPS2FPGA AXI Bridge
#define ALT_AXI_FPGASLVS_OFST (0xC0000000) // axi_master
#define HW_FPGA_AXI_SPAN (0x40000000) // Bridge span 1GB
#define HW_FPGA_AXI_MASK ( HW_FPGA_AXI_SPAN - 1 )




int main (int argc, char *argv[]) {
    int i=0;
    printf("argc %d",argc);

    // app program name 
    printf("exe %s", argv[0]);

    for (i=1; i< argc; i++) {
       printf("\narg%d=%s", i, argv[i]);
    }


   //pointer to the different address spaces

   
   void *virtual_base;
   int fd;
   // void *axi_virtual_base; // not used

   //void *h2p_lw_myBus_addr;
   
   
   //void *h2p_lw_reg0_out_addr;

   void *h2p_lw_reg1_in_addr;
 
   // map the address space for the LED registers into user space so we can interact with them.
   // we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

   if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
      printf( "ERROR: could not open \"/dev/mem\"...\n" );
      return( 1 );
   }
  


   //lightweight HPS-to-FPGA bridge
   virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

   if( virtual_base == MAP_FAILED ) {
      printf( "ERROR: mmap() failed...\n" );
      close( fd );
      return( 1 );
   }
   
 

   /* commented out: not used:
   
   //HPS-to-FPGA bridge
   axi_virtual_base = mmap( NULL, HW_FPGA_AXI_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd,ALT_AXI_FPGASLVS_OFST );

   if( axi_virtual_base == MAP_FAILED ) {
      printf( "ERROR: axi mmap() failed...\n" );
      close( fd );
      return( 1 );
   }
   */

/*
//-----------------------------------------------------------
   //configure the LEDs of the Golden Reference design
   h2p_lw_led_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_LED_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
   
   printf( "\n\n\n-----------Set the LEDs on-------------\n\n" );
   *(uint32_t *)h2p_lw_led_addr = 0b10111101;
   sleep(1);
   printf( "\n\n\n-----------Set the LEDs off-------------\n\n" );
   *(uint32_t *)h2p_lw_led_addr = 0b00000000;
   sleep(1);
   printf( "\n\n\n-----------Set the LEDs on-------------\n\n" );
   *(uint32_t *)h2p_lw_led_addr = 0b11111111;
   sleep(1);
   printf( "\n\n\n-----------Set the LEDs off-------------\n\n" );
   *(uint32_t *)h2p_lw_led_addr = 0b00000000;
   sleep(1);
   
   // buttons 
   h2p_lw_button_addr = virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_BUTTON_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
   // read buttons
   printf( "\n\n\n-----------read buttons: press buttons (1-to-2)-------------\n\n" );
   printf( "buttons %d\n", *((uint32_t *)h2p_lw_button_addr));
   sleep(1);
   printf( "buttons %d\n", *((uint32_t *)h2p_lw_button_addr));
   sleep(1);
 */   
   // PIO outputs
  // h2p_lw_reg0_out_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_REG0_OUT_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

   // PIO inputs  
   h2p_lw_reg1_in_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + PIO_REG1_BASE ) & ( unsigned long)( HW_REGS_MASK ) );

    

for(  i=0;i<=255;i++){
         
      //write to input
      *(uint32_t *)h2p_lw_reg1_in_addr = i;
      printf( "h2p_lw_reg1_in_addr %d\n", *((uint32_t *)h2p_lw_reg1_in_addr));
     

      usleep(500000);
   }


	  
   if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
      printf( "ERROR: munmap() failed...\n" );
      close( fd );
      return( 1 );
   }

   /* commented out not used
   if( munmap( axi_virtual_base, HW_FPGA_AXI_SPAN ) != 0 ) {
      printf( "ERROR: axi munmap() failed...\n" );
      close( fd );
      return( 1 );
   }
   */

   close( fd );
   return( 0 );
}