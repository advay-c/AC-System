# Air Conditioning System ATMEGA 324PA


## Functions

**Compare**

```c++
void compare()
{
  if (keycode == power)   
  {
    press++;    
  }
  if (keycode == volumeinc)   
  {
    ACtemperature ++;   
    if (ACtemperature >= 16 && ACtemperature <= 30) 
    {
      temperature++; 
      LCDdisplay(); 
    }
    if (ACtemperature < 16) 
    {
      ACtemperature = 16;
    }
    if (ACtemperature > 30) 
    {
      ACtemperature = 30; 
    }
  }
  if (keycode == (volumedec)) 
  {
    ACtemperature --; 
    if (ACtemperature >= 16 && ACtemperature <= 30) 
    {
      temperature--;  
      LCDdisplay(); 
    }
    if (ACtemperature < 16) 
    {
      ACtemperature = 16; 
    }
    if (ACtemperature > 30) 
    {
      ACtemperature = 30; 
    }
  }
}
```

**LCDdisplay**

```c++
void LCDdisplay()
{
  lcd.cmd(0x01); 
  lcd.string("Set temp:   "); 
  lcd.showvalue(temperature);
  lcd.line2(0); 
  lcd.string("Room temp:  "); 
  lcd.showvalue(Tc);  
}
```


## explanation

once power button on IR remote is pressed, the ac will turn on and the thermistor will detect the current room temperature. That room temperature will be displayed on the lcd screen.

If the set temperature is less then the room temperature, then the dc motor will be enabled.

The desired room temperature is set by volume+ and volume- button of the IR remote.

Currently, the room temperature is set to 16-30 degrees, therefore we cannot go under 16 degrees and above 30.
