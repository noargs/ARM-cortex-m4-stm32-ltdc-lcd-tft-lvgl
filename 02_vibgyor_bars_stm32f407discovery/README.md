## Displaying VIBGYOR bars on the display
      
			
> Connection details of **ILI9341** chip with **STM32f407 discovery** as follows:    
      
			
<img src="images/connection_f407.png" alt="Connection of ILI9341 LCD Chip with STM32F407" title="Connection of ILI9341 LCD Chip with STM32F407">			
       
			 
			 
<img src="images/vibgyor_bars.png" alt="Vibgyor bars" title="Vibgyor bars">		  
              
          
												
<img src="images/steps.png" alt="Steps involved in developing the project" title="Steps involved in developing the project">	       
     
		 
## Setup main system clock (Sysclk)		  
      
We will first configure SYSCLK for the maximum value a microcontroller can achieve for the display VIBGYOR bars exercise.     
        
<img src="images/sysclk_3boards.png" alt="Sysclk / PLL clock of different MCUs" title="Sysclk / PLL clock of different MCUs">	      
        
        
In the microcontroller STM32F429IDISCOVERY board, the maximum value for the SYSCLK could be 180MHz. That is the maximum speed of the SYSCLK.  And for this STM32F746GDISCOVERY microcontroller, it could be 216MHz, and for the STM32F407DISCOVERY board, it could be 168MHz.			
                
								
## Main PLL configuration								
           
To configure clock for maximum value we must use PLL engine to configure the system clock   
     
- PLL_M(Controls input to the PLL VCO and PLLSAI VCO) 
- PLL_N(Multiplier)
- PLL_P(Divider) 		 					 
        
<img src="images/clock_tree.png" alt="Clock Tree Diagram" title="Clock Tree Diagram">	      
       
			  				
Above Clock tree diagram is nearly same for all the microcontrollers from ST. HSI, HSE and PLLCLK is the main part of the clock tree. We can select the SYSCLK out of HSI (16 Mhz for STM32F07 discovery board), HSE (8 MHz) or PLLCLK (168 Mhz) using the SW bit   
        
				
PLL stands for Phased Locked Loop (PLL). And this contains a block called VCO (Voltage Controlled Oscillator), which produces high-speed clocks. 	 
         
				 
<img src="images/rcc_pll.png" alt="PLL CFGR RCC register" title="PLL CFGR RCC register">	    
         
				  
					
<img src="images/rcc_cfgr.png" alt="RCC CFGR register" title="RCC CFGR register">	 									 
       
			 
## Program Flash wait state			 
          
<img src="images/flash_settings.png" alt="Flash wait state table" title="Flash wait state table">			
            
						
						
						
## PWR settings      
        
<img src="images/pwr_settings.png" alt="PWR Settings" title="PWR Settings">				
       
			 
			 
<img src="images/spi_interface.png" alt="SPI Interface" title="SPI Interface">				 
			 
			 								 			
        						
				