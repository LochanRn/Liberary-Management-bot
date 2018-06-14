int M1[] =  { 41, 39, 7 };                        // A, B, PWM long 0-1 up
int M2[] =  { 53, 51, 6 };                        // A, B, PWM long 0-1 up
int M3[] =  { 29, 31, 5 };                        // A, B, PWM long 0-1 up

int CH[] = { A3, A1, A2 };

int pulse[3] = {};
int mapper[3] = {};

int i,limit = 20;

void setup() {
  for (i = 0; i < 3; i++) {  // LA outputs
    pinMode(M1[i], OUTPUT);
    pinMode(M2[i], OUTPUT);
    pinMode(M3[i], OUTPUT);
  }
  for (i = 0; i < 3; i++)   // RC INPUT
    pinMode(CH[i], INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  rc();
  control(mapper[0] + mapper[1], 20, M1, abs(mapper[0] + mapper[1]));
  control(mapper[0] - mapper[1], 20, M2, abs(mapper[0] - mapper[1]));
  if(abs(mapper[0])>20){
    control(mapper[0], 20, M3, (abs(mapper[0])/2)+22);
  }
  else{
    control(mapper[2], 20, M3, abs(mapper[2]));
  }
}
  void rc() {
  for (i = 0; i < 3; i++) {
    pulse[i] = pulseIn(CH[i], HIGH);
  }
    mapper[0] = map(pulse[0], 1028, 1842, 100, -100);
    mapper[1] = map(pulse[1], 1028, 1842, 100, -100);
    mapper[2] = map(pulse[2], 1852, 1028, 100, -100);
}

void control(int inp, int lim, int M[], int pwm) {
  if (abs(inp) <= lim)  act(M, 0, 0, 0);
  else if (inp >  lim)  act(M, 0, 1, pwm);
  else if (inp < -lim)  act(M, 1, 0, pwm);
  else act(M, 0, 0, 0);
}
void act(int arr[], boolean A, boolean B, int pwm) {
  digitalWrite(arr[0], A);
  digitalWrite(arr[1], B);
  analogWrite(arr[2], pwm);
}
