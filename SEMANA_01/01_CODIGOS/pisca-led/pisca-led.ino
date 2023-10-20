int G = 27; // Verde
int A = 26; // Amarelo
int R = 32; // Vermelho

int DELAY = 500;
void setup() {
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(R, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(G, HIGH);
  delay(DELAY);
  digitalWrite(G, LOW);
  delay(DELAY);

  digitalWrite(A, HIGH);
  delay(DELAY);
  digitalWrite(A, LOW);
  delay(DELAY);

  digitalWrite(R, HIGH);
  delay(DELAY);
  digitalWrite(R, LOW);
  delay(DELAY);

}
