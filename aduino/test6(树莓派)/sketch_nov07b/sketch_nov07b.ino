void setup() 
{
  Serial.begin(9600); // 9600 bps
}
void loop()
{
  if ( Serial.available())
    {
      if('s' == Serial.read())
        Serial.println("Hello Raspberry,I am Arduino.");
      else{
        Serial.println("你发的是什么？");  
      }
     }
}
