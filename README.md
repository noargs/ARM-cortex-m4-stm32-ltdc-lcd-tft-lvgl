## ARM Cortex M4 stm32 LTDC LCD-TFT LVGL
      
			
Embedded graphic system, Interfacing over SPI, and building graphical UI using LVGL    
    
<img src="images/embedded_graphics_system.png" alt="embedded_graphics_system" title="Embedded graphics system">		 
       
- The display and the microcontroller board are connected with some interface.			 
      
- There are different interface techniques like parallel interfacing, serial interfacing, etc    
     
- There are several display modules available, based on the technology used to lit the pixels of the display, in the market (i.e. LCD, LED, Plasma, OLED displays etc.) 		 	
      
- In LCD itself there are various variants like TFT, IPS, etc    
       
- A display module (LCD) has its own circuitry based on some Controller (Display driver chip)   
            
- And that Display driver Chip interprets the signal, coming over this interface from Host (MCU), and controls the pixels of the display to show different colors or information which is being sent from the host.						  
      
- To show an image on the Display module, you have to convert that image into a stream of bytes and store it somewhere in the microcontroller’s memory (i.e. Flash memory or RAM). 
      
-	And finally stream those bytes over the microcontroller interface to the Display module. And Display driver chip of Display module interprets the signals and it controls the pixels of the display to show that information on the Display. 		
         
<img src="images/embedded_roaring.png" alt="embedded_graphics_system_essential_parts" title="Essential parts of Embedded graphics system">				 
				   
					  
### Important parts of the Embedded graphics system		  
         
				 
**Microcontroller (Host)**      
        
- Processor (Executes your code, updates frame buffer)    
     
- RAM (Frame buffer)         
      
- Flash (static images, fonts, texts, etc)				
           
					  
**Display Module**						
						
- Glass(where you see the graphics)       
      
- Driver chip (Interprets the signals sent by the host, generates required electric signals and voltages to lit the pixels of the display panel)						
						
						
> **Frame buffer**: A memory area which holds the pixel values of the frame to be updated on the display.    						
						
**Display controller (LCD controller)**								
			
- This is present at the Host (MCU). It generates display timing signals and transmits the pixel data over the interface						
						
- In MCU, There is a peripheral called LTDC (LCD-TFT Display Controller). It is also a bus master. It can directly take the pixel data from the Frame buffer and send it to the Display module over the LTDC interface. _No processor intervention is required_     
      
**External memories**		 									
						
- External Flash(your code + graphics components(images, texts) may not fit inside the internal flash)						
				
- And sometimes you may need two Frame buffers, in that case, the internal RAM may not be sufficient.						
						
						
**Graphics library (LVGL, TouchGFX)**								
		
- You may use already available graphic stack or libraries in your application, like LVGL, Touch graphics, or TouchGFX						
							
- Also called graphics middlewares, which will be helpful when building complex interactive graphics application.    
       
			 
**DMA**								
				
- Helps to transfer Frame buffer to display without the intervention of the CPU					 								 		

- To transfer graphic details from flash to Frame buffer without the intervention of the CPU			      
			 			 					