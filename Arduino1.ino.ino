int ledPin = 4;           
int ldrPin = 39;          
int trigPin = 7;          
int echoPin = 8;          
long duration;        
int distance;             
int ldrValue;

void setup() {
  pinMode(ledPin, OUTPUT);    
  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);    
  Serial.begin(9600);        
}

void loop() {
 
  ldrValue = analogRead(ldrPin);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);       
  distance = duration * 0.034 / 2;       
  Serial.print("Distance: ");
  Serial.println(distance);

  
  if (distance <= 300 && ldrValue > 2000) {
    analogWrite(ledPin, 50);             
  } else {
    analogWrite(ledPin, 255);            
  }

  delay(100); 

}
import psycopg2

app = Flask(_name_)


conn = psycopg2.connect(
    dbname="your_db_name",  # Replace with your database name
    user="your_user",       # Replace with your username
    password="your_password",  # Replace with your password
    host="localhost",       # Or your server's IP
    port="5432"             # Default PostgreSQL port
)
cur = conn.cursor()

@app.route('/insert_data')
def insert_data():
    
    ldr_value = request.args.get('ldr')
    distance = request.args.get('distance')

    # Insert data into PostgreSQL
    if ldr_value is not None and distance is not None:
        try:
            # Insert into the table
            cur.execute("INSERT INTO sensor_data (ldr_value, distance) VALUES (%s, %s)", (ldr_value, distance))
            conn.commit()
            return "Data inserted successfully!"
        except Exception as e:
            conn.rollback()
            return f"Error: {str(e)}"
    else:
        return "Missing data"

if _name_ == '_main_':
    # Run Flask app on port 5000
    app.run(host='0.0.0.0', port=5000)