#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
//分数
int sorce;

//像素点结构体
typedef struct kuai{
  byte x;
  byte y;
}kuai;
kuai snake[64];//蛇
//蛇初始化
int snake_length;
int yuan_x;
int yuan_y;

//上上下下
kuai xiaqiang[2];//下墙
kuai shangqiang[2];//上墙
kuai brid;

LiquidCrystal_I2C lcd(0x27, 16, 2);
const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 5, 4, 3, 2 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 9, 8, 7, 6 }; // Pins connected to R1, R2, R3, R4
Keypad keypad1 = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);




void meun(){
  lcd.setCursor(2, 0);
  lcd.print("Games:");
  lcd.setCursor(5, 1);
  lcd.print("1.Snakes ");
  lcd.setCursor(5, 2);
  lcd.print("2.up down");
  lcd.setCursor(5, 3);
  lcd.print("3.exit");
}




void snakechange(char key){
  switch(key){
    case '2'://up
            //删掉原来的
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              lcd.print(" ");
            }

            //改变坐标
             for(int i=snake_length-1;1<=i;i--){
               snake[i].x=snake[i-1].x;
               snake[i].y=snake[i-1].y;
            }
            snake[0].y=(snake[0].y-1)%4;
            //重画
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              if(i==0)
                lcd.print("O");
              else
                lcd.print("o");
            }
            break;
    case '5'://down
            //删掉原来的
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              lcd.print(" ");
            }

            //改变坐标
            for(int i=snake_length-1;1<=i;i--){
               snake[i].x=snake[i-1].x;
               snake[i].y=snake[i-1].y;
            }
            snake[0].y=(snake[0].y+1)%4;
            //重画
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              if(i==0)
                lcd.print("O");
              else
                lcd.print("o");
            }
            break;
    case '4'://<-
            //删掉原来的
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              lcd.print(" ");
            }
            //改变坐标
             for(int i=snake_length-1;1<=i;i--){
               snake[i].x=snake[i-1].x;
               snake[i].y=snake[i-1].y;
            }
            snake[0].x=snake[0].x-1;
            if(snake[0].x==1){
              snake[0].x=13;
            }
            //重画
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              if(i==0)
                lcd.print("O");
              else
                lcd.print("o");
            }
            break;
    case '6'://->
            //删掉原来的
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              lcd.print(" ");
            }
            //改变坐标
            for(int i=snake_length-1;1<=i;i--){
               snake[i].x=snake[i-1].x;
               snake[i].y=snake[i-1].y;
            }
            snake[0].x=snake[0].x+1;
            if(snake[0].x==14){
              snake[0].x=2;
            }
            //重画
            for(int i=0;i<snake_length;i++){
              lcd.setCursor(snake[i].x, snake[i].y);
              if(i==0)
                lcd.print("O");
              else
                lcd.print("o");
            }
            break;
  }

}

int foodpd(kuai food){
    if((snake[0].x+1==food.x||snake[0].x-1==food.x )&& snake[0].y==food.y){
      yuan_x=snake[snake_length-1].x;
      yuan_y=snake[snake_length-1].y;
    }else if(snake[0].x==food.x&&(snake[0].y+1==food.y||snake[0].y-1==food.y )){
      yuan_x=snake[snake_length-1].x;
      yuan_y=snake[snake_length-1].y;
    }else if(snake[0].x==food.x && snake[0].y==food.y){
      //改变分数
      sorce=sorce+1;
      //显示分数
      lcd.setCursor(15, 2);
      lcd.print(sorce);
      //增加蛇长度
      snake_length=snake_length+1;
      //增加新点
      snake[snake_length-1].x=yuan_x;
      snake[snake_length-1].y=yuan_y;
      //重画
      for(int i=0;i<snake_length;i++){
        lcd.setCursor(snake[i].x, snake[i].y);
        lcd.print("");
      }
      for(int i=0;i<snake_length;i++){
        lcd.setCursor(snake[i].x, snake[i].y);
        if(i==0)
          lcd.print("O");
        else
          lcd.print("o");
      }
      //可以产生新food
      return 0;
    }
    return 1;
}

kuai randfood(){
  //随机生成
  byte x=random(4,14);
  byte y=random(0,3);
  kuai food;
  food.x=x;
  food.y=y;

  lcd.setCursor(food.x, food.y);
  lcd.print("*");
  return food;

}

int eatmepd(){
  byte x=snake[0].x;
  byte y=snake[0].y;
  for(int i=1;i<snake_length;i++){
      if(x==snake[i].x && y==snake[i].y){
        return 1;
      }
  }
  return 0;
}

void Snakes_game(){
  Keypad keypad2 = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
  char key=keypad2.getKey();
  //初始化
  //背景
  for(int i=0;i<=3;i++){
      lcd.setCursor(1, i);
      lcd.print("|");
      lcd.setCursor(14, i);
      lcd.print("|");

  }
  lcd.setCursor(15, 1);
  lcd.print("sorce");
  lcd.setCursor(15, 2);
  lcd.print(sorce);
  //蛇初始化
  snake[0].x=7;
  snake[0].y=2;
  lcd.setCursor(snake[0].x, snake[0].y);
  lcd.print("O");
  snake_length=1;
  int flag=0;
  kuai food;
  int gameover=0;
  while(key!='0' && gameover==0){
      if(flag==0){//如果food被吃则生成food
        food=randfood();//随机生成food
        flag=1;
      }
    Keypad keypad3 = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
    char key1=keypad3.getKey();
    key=key1;
    Serial.println(key1);
    //判断蛇走的方向,并且走
    snakechange(key1);
    delay(100);
    //吃food判断
    flag=foodpd(food);
    //判断蛇是否咬到自己
    gameover=eatmepd();


  }
  if(gameover==1){
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("Game Over!");
    lcd.setCursor(6, 2);
    lcd.print("Sorce:");
    lcd.setCursor(12, 2);
    lcd.print(sorce);
    delay(2000);
  }
  

  
}


void Snakes(){
  
  //说明
  lcd.setCursor(0, 0);
  lcd.print("exit please press 0");
  delay(1000);
  //游戏
  lcd.clear();
  Snakes_game();
  
}

void flychange(char key){
  switch(key){
    case '2'://up
            //删掉原来的
            lcd.setCursor(brid.x, brid.y);
            lcd.print(" ");

            //改变坐标
            brid.y=(brid.y-1);
            if(brid.y==-1){
              brid.y=0;
            }
            //重画
            lcd.setCursor(brid.x, brid.y);
            lcd.print("O");
            break;
    case '5'://down
            //删掉原来的
            lcd.setCursor(brid.x, brid.y);
            lcd.print(" ");

            //改变坐标
            brid.y=(brid.y+1);
            if(brid.y==4){
              brid.y=3;
            }
            //重画
            lcd.setCursor(brid.x, brid.y);
            lcd.print("O");
            break;
  }
    

}

void qiangchange(){
  for(int i=0;i<=1;i++){
    
      lcd.setCursor(shangqiang[i].x, shangqiang[i].y);
      lcd.print(" ");
      shangqiang[i].x=shangqiang[i].x-1;
      if(shangqiang[i].x<3){
        shangqiang[i].x=19;
      }
      lcd.setCursor(shangqiang[i].x, shangqiang[i].y);
      lcd.print("|");

      lcd.setCursor(xiaqiang[i].x, xiaqiang[i].y);
      lcd.print(" ");
      xiaqiang[i].x=xiaqiang[i].x-1;
      if(xiaqiang[i].x<3){
        xiaqiang[i].x=19;
      }
      lcd.setCursor(xiaqiang[i].x, xiaqiang[i].y);
      lcd.print("|");
    
  }
}

int collisionpd(){//碰撞返回1,球的坐标为（5，2）,通过返回2
    if((shangqiang[1].x==brid.x&&shangqiang[1].y>=brid.y)||(xiaqiang[0].x==brid.x&&xiaqiang[0].y<=brid.y))
        return 1;
    else if((shangqiang[1].x==brid.x&&shangqiang[1].y<=brid.y)||(xiaqiang[0].x==brid.x&&xiaqiang[0].y>=brid.y)) 
      return 2;
    else
      return 0;

}

void fly_game(){
  Keypad keypad2 = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
  char key=keypad2.getKey();
  //初始化
  //障碍
  //上墙
  shangqiang[0].x=8;
  shangqiang[1].x=8;
  for(int i=0;i<=1;i++){
      shangqiang[i].y=i;
  }
  //draw
  for(int i=0;i<=1;i++){
    lcd.setCursor(shangqiang[i].x, shangqiang[i].y);
    lcd.print("|");
  }

  //下墙
  xiaqiang[0].x=15;
  xiaqiang[1].x=15;
  for(int i=0;i<=1;i++){
    xiaqiang[i].y=i+2;
  
  }
   //draw
  for(int i=0;i<=1;i++){
     
        lcd.setCursor(xiaqiang[i].x, xiaqiang[i].y);
        lcd.print("|");
    
  }

  //鸟
  brid.x=5;
  brid.y=2;
  lcd.setCursor(brid.x, brid.y);
  lcd.print("O");
  //分数
  sorce=0;
  lcd.setCursor(0, 0);
  lcd.print(sorce);
  bool gameover=0;
  while(key!='0' && gameover==0){
    Keypad keypad3 = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
    //障碍向左移
    qiangchange();
    
    char key1=keypad3.getKey();
    key=key1;
    //改变上下
    flychange(key1);
    delay(200);
    lcd.setCursor(brid.x, brid.y);
    lcd.print("O");

    //判断碰撞
    int pz;
    pz = collisionpd();
    if(pz==2){
      sorce=sorce+1;
      lcd.setCursor(0,0);
      lcd.print(sorce);
    }else if(pz==1){
      gameover=1;
    }
  }
  if(gameover==1){
    lcd.clear();
    lcd.setCursor(6, 1);
    lcd.print("Game Over!");
    lcd.setCursor(6, 2);
    lcd.print("Sorce:");
    lcd.setCursor(12, 2);
    lcd.print(sorce);
    delay(2000);
  }
}



void fly(){
  
  //说明
  lcd.setCursor(0, 0);
  lcd.print("exit please press 0");
  delay(1000);
  //游戏
  lcd.clear();
  fly_game(); 
}

void setup() {
  Serial.begin(9600);

  lcd.init(); 
  lcd.backlight();
  lcd.begin(20, 4);

  randomSeed(analogRead(0));

  meun();
}

void loop() {
  char key = keypad1.getKey();
  Serial.println(key);
  while(key!=NO_KEY){
    if(key=='1'){
      lcd.clear();
      Snakes();
    }else if(key=='2'){
      lcd.clear();
      fly();
    }else if(key=='3'){
      lcd.clear();
      lcd.setCursor(7, 1);
      lcd.print("Bye!");
      lcd.setCursor(0, 2);
      lcd.print("Please close power!");
      delay(1000);
      lcd.clear();
      while(1);
    }
    lcd.clear();
    meun();
    key = keypad1.getKey();
    Serial.println(key);  
  }
  
}