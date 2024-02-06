## Roaring tiger demo on STM32F407-DISC board with external LCD
      
			
Here we are using SPI communication along with a few control signals. And the SPI communication is used to send commands, its parameters, and the RGB data   
    
<img src="images/spi_lcd_board.png" alt="STM32F4Discovery with LCD over SPI" title="STM32F4Discovery with LCD over SPI">		 
       
       
Our LCD-TFT display module is based on **ILI9341** chip
         
<img src="images/lcd_tft_datasheet_sc.png" alt="ILI9341 chip datasheet screenshot" title="ILI9341 chip datasheet screenshot">	              
										 			 
													 
Download [Datasheet](http://www.lcdwiki.com/res/MSP2402/ILI9341_Datasheet.pdf), [User Manual](http://www.lcdwiki.com/res/MSP2402/2.4inch_SPI_Module_MSP2402_User_Manual_EN.pdf), and [Schematic](http://www.lcdwiki.com/res/MSP2402/MSP2402-2.4-SPI.pdf) of `ILI9341 chip`													 
        
				
### Connection details     
       
<img src="images/lcd_connection_with_stm32f4discovery.png" alt="lcd_connection_with_stm32f4discovery" title="LCD connection with stm32f4discovery">				      
				 				   

