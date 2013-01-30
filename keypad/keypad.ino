void setup()
{
  pinMode(8,INPUT);
  pinMode(3,INPUT);
  pinMode(5,INPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(8,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(5,HIGH);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  Serial.begin(9600);
}

int i, code[4], codeResult = 0, msPassed;

void setRowLow(int row)
{
  digitalWrite(row,LOW);
}

void setColLow(int col)
{
  digitalWrite(col,LOW);
}

void resetRows()
{
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
}

int readKeypad()
{
  int i = 0;
  
  int keypad;

  for(i=0;i<12;i++)
  {
    resetRows();

    switch(i)
    {
      case 1:
      case 2:
      case 3:
        setRowLow(2);
      break;
      
      case 4:
      case 5:
      case 6:
        setRowLow(7);
      break;
      
      case 7:
      case 8:
      case 9:
        setRowLow(6);
      break;
      
      case 10:
      case 11:
      case 0:
        setRowLow(4);
      break;
    }

    switch(i)
    {
      case 1:
        if (digitalRead(3) == LOW)
        {
          while(digitalRead(3) == LOW);
          return 1;
        }   
      break;
      case 4:
        if (digitalRead(3) == LOW)
        {
          while(digitalRead(3) == LOW);
          return 4;
        }
      break;
      case 7:
        if (digitalRead(3) == LOW)
        {
          while(digitalRead(3) == LOW);
          return 7;
        }
      break;
      case 10: // *
        if (digitalRead(3) == LOW)
        {
          while(digitalRead(3) == LOW);
          return 10;
        }
      break;
      
      case 2:
        if (digitalRead(8) == LOW)
        {
          while(digitalRead(8) == LOW);
          return 2;
        }
      break;
      case 5:
        if (digitalRead(8) == LOW)
        {
          while(digitalRead(8) == LOW);
          return 5;
        }
      break;
      case 8:
        if (digitalRead(8) == LOW)
        {
          while(digitalRead(8) == LOW);
          return 8;
        }
      break;
      case 0:
        if (digitalRead(8) == LOW)
        {
          while(digitalRead(8) == LOW);
          return 0;
        }
      break;
      
      case 3:
        if (digitalRead(5) == LOW)
        {
          while(digitalRead(5) == LOW);
          return 3;
        }
      break;
      case 6:
        if (digitalRead(5) == LOW)
        {
          while(digitalRead(5) == LOW);
          return 6;
        }
      break; 
      case 9:
        if (digitalRead(5) == LOW)
        {
          while(digitalRead(5) == LOW);
          return 9;
        }
      break;
      case 11: // #
        if (digitalRead(5) == LOW)
        {
          while(digitalRead(5) == LOW);
          return 11;
        }
      break;
    }
  }

  return -1;
}

void FlashLED()
{
  int i;
  for(i=0;i<16;i++)
  {
    digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(13,LOW);
    delay(50);
  }
}

int checkCode()
{
  if (code[0] == 1 && code[1] == 2 && code[2] == 3 && code[3] == 4)
  {
    return 1;
  } else {
    return 0;
  }
}

void loop()
{
  int keypad = readKeypad();

  if (keypad != -1)
  {
    msPassed = 0;
    code[i++] = keypad;

    if (i == 4)
    {
      codeResult = checkCode();
      if (codeResult == 1)
      {
        // Correct
        digitalWrite(13,HIGH);
        delay(2000);
        digitalWrite(13,LOW);
      } else {
        FlashLED();
      }
      i = 0;
    }
  }

  delay(50);
  msPassed = msPassed + 50;

  // Code entry timeout
  if (msPassed >= 5000)
  {
    i = 0;
    msPassed = 0;
  }
}
