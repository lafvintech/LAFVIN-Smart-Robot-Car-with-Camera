5. Function Lessons
===================

.. raw:: html

   <div class="upload-program-container">
     <div class="upload-header">
       <h2 id="function-lessons-section" style="margin:0; font-size:inherit; color:inherit;">Function Lessons</h2>
       <img src="_static/icon_title.png" alt="car" class="car-icon">
     </div>

     <div class="text-orange">Learn each function step by step</div>
     <div class="text-blue">
       This chapter introduces six single-function example programs for the Smart Robot Car.<br>
       Each lesson focuses on one feature only, so you can upload the code and directly observe what the car does.<br>
       Before starting these lessons, please complete <a href="upload_arduino.html" style="color: #0066cc; text-decoration: underline;">Upload Program to Arduino UNO Board</a> first.
     </div>
     <div style="margin-top: 18px; text-align: center;">
       <a href="_static/Lesson_Code.zip" style="display:inline-block; background:#4CAF50; border:2px solid #43A047; border-radius:25px; box-shadow:0 4px 12px rgba(76,175,80,0.3); text-decoration:none; color:white; font-weight:600; font-size:18px; padding:12px 28px;" download>Download Lesson Code</a>
     </div>
   </div>

Lesson 1 Move
---------------

.. raw:: html

   <div class="upload-program-container">
     <div class="upload-header" style="margin-top: 20px;">
       <h2 id="move-lesson-section" style="margin:0; font-size:inherit; color:inherit;">Lesson 1 Move</h2>
       <img src="_static/icon_title.png" alt="car" class="car-icon">
     </div>

     <div class="text-orange">Function</div>
     <div class="text-blue">
       This lesson is used for basic motor testing. After the code is uploaded, the two drive motors will run automatically without requiring any APP or remote control operation.
     </div>

     <div class="text-orange">What happens after upload</div>
     <div class="text-blue">
       The car moves forward for 2 seconds, stops briefly, moves backward for 2 seconds, then stops briefly and repeats the cycle.
     </div>

     <div class="text-orange">How to use</div>
     <div class="text-blue">
      <span style="color: #ec4d08ff; font-weight: 700;">Code location:</span> <span style="display: inline-block; color: #bb901aff; font-weight: 700; background: #fff4e8; border: 1px solid #f3cfaa; border-radius: 8px; padding: 2px 8px;">Lesson_Code/SmartRobotCar_Move/SmartRobotCar_Move.ino</span><br>
      <span style="color: #ec4d08ff; font-weight: 700;">Code upload method:</span> <a href="upload_arduino.html" style="color: #bb901aff; font-weight: 700; text-decoration: none; border-bottom: 2px solid #bb901aff;">Upload Program to Arduino UNO Board</a><br><br>

      1. Open <span style="color: #bb901aff; font-weight: 700;">"SmartRobotCar_Move.ino"</span> in Arduino IDE.<br>
      2. Upload the code to the Arduino UNO board.<br>
      3. Place the car on a safe and open surface.<br>
      4. Turn on the power and observe whether the left and right motors rotate correctly.
     </div>

     <div class="text-orange">Tips</div>
     <div class="text-blue">
       This lesson is suitable for checking whether the motors, motor driver and battery power are working normally.<br>
       If the moving direction is opposite to the expected direction, please check the motor wiring or motor direction settings.<br>
       Lift the car slightly during the first test to avoid sudden movement on the desk.
     </div>
   </div>

Lesson 2 RGB
--------------

.. raw:: html

   <div class="upload-program-container">
     <div class="upload-header" style="margin-top: 20px;">
       <h2 id="rgb-lesson-section" style="margin:0; font-size:inherit; color:inherit;">Lesson 2 RGB</h2>
       <img src="_static/icon_title.png" alt="car" class="car-icon">
     </div>

     <div class="text-orange">Function</div>
     <div class="text-blue">
       This lesson demonstrates the RGB LED on the robot car. It keeps the same LED data pin and FastLED control style used by the integrated program SmartRobotCar_Main_V1.
     </div>

     <div class="text-orange">What happens after upload</div>
     <div class="text-blue">
       The RGB LED automatically cycles through red, green, blue, yellow, cyan, violet, white and off.<br>
       Each color is displayed for about 1 second so you can clearly observe the change.
     </div>

     <div class="text-orange">How to use</div>
     <div class="text-blue">
      <span style="color: #ec4d08ff; font-weight: 700;">Code location:</span> <span style="display: inline-block; color: #bb901aff; font-weight: 700; background: #fff4e8; border: 1px solid #f3cfaa; border-radius: 8px; padding: 2px 8px;">Lesson_Code/SmartRobotCar_RGB/SmartRobotCar_RGB.ino</span><br>
      <span style="color: #ec4d08ff; font-weight: 700;">Code upload method:</span> <a href="upload_arduino.html" style="color: #bb901aff; font-weight: 700; text-decoration: none; border-bottom: 2px solid #bb901aff;">Upload Program to Arduino UNO Board</a><br><br>

      1. Open <span style="color: #bb901aff; font-weight: 700;">"SmartRobotCar_RGB.ino"</span> in Arduino IDE.<br>
      2. Upload the code to the Arduino UNO board.<br>
      3. Turn on the power and observe the RGB LED on the car body.<br>
      4. Check whether the LED can display all colors in sequence.
     </div>

     <div class="text-orange">Tips</div>
     <div class="text-blue">
       This lesson uses the same RGB LED pin as the integrated program: digital pin 4.<br>
       If Arduino IDE prompts that FastLED is missing, please install the FastLED library first.<br>
       If the LED does not light up, check the RGB module connection and power supply.
     </div>
   </div>

Lesson 3 Servo
----------------

.. raw:: html

   <div class="upload-program-container">
     <div class="upload-header" style="margin-top: 20px;">
       <h2 id="servo-lesson-section" style="margin:0; font-size:inherit; color:inherit;">Lesson 3 Servo</h2>
       <img src="_static/icon_title.png" alt="car" class="car-icon">
     </div>

     <div class="text-orange">Function</div>
     <div class="text-blue">
       This lesson demonstrates the SG90 servo on the robot car. It uses the same servo pin and center position as the integrated program SmartRobotCar_Main_V1.
     </div>

     <div class="text-orange">What happens after upload</div>
     <div class="text-blue">
       The servo rotates to the left position, returns to the center, rotates to the right position, then returns to the center again.<br>
       The movement repeats automatically so you can test whether the servo responds smoothly.
     </div>

     <div class="text-orange">How to use</div>
     <div class="text-blue">
      <span style="color: #ec4d08ff; font-weight: 700;">Code location:</span> <span style="display: inline-block; color: #bb901aff; font-weight: 700; background: #fff4e8; border: 1px solid #f3cfaa; border-radius: 8px; padding: 2px 8px;">Lesson_Code/SmartRobotCar_Servo/SmartRobotCar_Servo.ino</span><br>
      <span style="color: #ec4d08ff; font-weight: 700;">Code upload method:</span> <a href="upload_arduino.html" style="color: #bb901aff; font-weight: 700; text-decoration: none; border-bottom: 2px solid #bb901aff;">Upload Program to Arduino UNO Board</a><br><br>

      1. Open <span style="color: #bb901aff; font-weight: 700;">"SmartRobotCar_Servo.ino"</span> in Arduino IDE.<br>
      2. Upload the code to the Arduino UNO board.<br>
      3. Turn on the power and observe the servo arm movement.<br>
      4. Confirm that the servo can reach left, center and right positions correctly.
     </div>

     <div class="text-orange">Tips</div>
     <div class="text-blue">
       This lesson uses the same servo pin as the integrated program: digital pin 10.<br>
       Make sure the servo horn is installed firmly before testing.<br>
       If the servo jitters or does not move normally, check the 5V power and signal wire connection.
     </div>
   </div>

Lesson 4 Follow
-----------------

.. raw:: html

   <div class="upload-program-container">
     <div class="upload-header" style="margin-top: 20px;">
       <h2 id="follow-lesson-section" style="margin:0; font-size:inherit; color:inherit;">Lesson 4 Follow</h2>
       <img src="_static/icon_title.png" alt="car" class="car-icon">
     </div>

     <div class="text-orange">Function</div>
     <div class="text-blue">
       This lesson demonstrates the auto-follow feature based on the ultrasonic sensor. After the code is uploaded, the robot car will automatically try to keep a suitable distance from the target in front of it.
     </div>

     <div class="text-orange">What happens after upload</div>
     <div class="text-blue">
       If the target is too close, the car moves backward.<br>
       If the target is at a suitable distance, the car stops.<br>
       If the target is a little farther away, the car moves forward.<br>
       If no valid target is detected, the car stops.
     </div>
     <img src="_static/V33.png" alt="follow lesson" style="max-width:100%; height:auto; margin-top:0px;margin-bottom:20px;">

     <div class="text-orange">How to use</div>
     <div class="text-blue">
      <span style="color: #ec4d08ff; font-weight: 700;">Code location:</span> <span style="display: inline-block; color: #bb901aff; font-weight: 700; background: #fff4e8; border: 1px solid #f3cfaa; border-radius: 8px; padding: 2px 8px;">Lesson_Code/SmartRobotCar_Follow/SmartRobotCar_Follow.ino</span><br>
      <span style="color: #ec4d08ff; font-weight: 700;">Code upload method:</span> <a href="upload_arduino.html" style="color: #bb901aff; font-weight: 700; text-decoration: none; border-bottom: 2px solid #bb901aff;">Upload Program to Arduino UNO Board</a><br><br>

      1. Open <span style="color: #bb901aff; font-weight: 700;">"SmartRobotCar_Follow.ino"</span> in Arduino IDE.<br>
      2. Upload the code to the Arduino UNO board.<br>
      3. Power on the robot car.<br>
      4. Stand or place an object in front of the ultrasonic sensor and slowly move it.<br>
      5. Observe how the car follows the target automatically.
     </div>

     <div class="text-orange">Tips</div>
     <div class="text-blue">
       Keep the target directly in front of the ultrasonic sensor for the best result.<br>
       The target should have a clear surface that can reflect ultrasonic waves.<br>
       Do not test too close to walls or cluttered objects, because they may affect distance detection.
     </div>
   </div>

Lesson 5 Line Tracking
------------------------

.. raw:: html

   <div class="upload-program-container">
     <div class="upload-header" style="margin-top: 20px;">
       <h2 id="linetrack-lesson-section" style="margin:0; font-size:inherit; color:inherit;">Lesson 5 Line Tracking</h2>
       <img src="_static/icon_title.png" alt="car" class="car-icon">
     </div>

     <div class="text-orange">Function</div>
     <div class="text-blue">
       This lesson demonstrates the line-tracking function. After the code is uploaded, the car reads the three line-tracking sensors and follows the line automatically.
     </div>

     <div class="text-orange">What happens after upload</div>
     <div class="text-blue">
       When the middle sensor detects the line, the car moves forward.<br>
       When the left or right sensor detects the line, the car turns to correct its direction.<br>
       When all sensors lose the line, the car performs a short scan to search for the track.
     </div>
     <img src="_static/V31.png" alt="line tracking lesson" style="max-width:100%; height:auto; margin-top:0px;margin-bottom:20px;">

     <div class="text-orange">How to use</div>
     <div class="text-blue">
      <span style="color: #ec4d08ff; font-weight: 700;">Code location:</span> <span style="display: inline-block; color: #bb901aff; font-weight: 700; background: #fff4e8; border: 1px solid #f3cfaa; border-radius: 8px; padding: 2px 8px;">Lesson_Code/SmartRobotCar_LineTrack/SmartRobotCar_LineTrack.ino</span><br>
      <span style="color: #ec4d08ff; font-weight: 700;">Code upload method:</span> <a href="upload_arduino.html" style="color: #bb901aff; font-weight: 700; text-decoration: none; border-bottom: 2px solid #bb901aff;">Upload Program to Arduino UNO Board</a><br><br>

      1. Open <span style="color: #bb901aff; font-weight: 700;">"SmartRobotCar_LineTrack.ino"</span> in Arduino IDE.<br>
      2. Upload the code to the Arduino UNO board.<br>
      3. Prepare a clear black line on a light background.<br>
      4. Place the robot car so that the line-tracking sensors are above the line.<br>
      5. Power on the robot car and observe the tracking effect.
     </div>

     <div class="text-orange">Tips</div>
     <div class="text-blue">
       The contrast between the line and the background should be obvious.<br>
       Keep the line smooth and wide enough for the three sensors to detect reliably.<br>
       If tracking is unstable, check the height and alignment of the line-tracking module.
     </div>
   </div>

Lesson 6 Obstacle Avoidance
-----------------------------

.. raw:: html

   <div class="upload-program-container">
     <div class="upload-header" style="margin-top: 20px;">
       <h2 id="obstacle-lesson-section" style="margin:0; font-size:inherit; color:inherit;">Lesson 6 Obstacle Avoidance</h2>
       <img src="_static/icon_title.png" alt="car" class="car-icon">
     </div>

     <div class="text-orange">Function</div>
     <div class="text-blue">
       This lesson demonstrates the obstacle-avoidance function. After the code is uploaded, the car will move forward, detect obstacles with the ultrasonic sensor, and choose another direction automatically.
     </div>

     <div class="text-orange">What happens after upload</div>
     <div class="text-blue">
       The car moves forward when the path is clear.<br>
       When an obstacle is detected ahead, the car stops.<br>
       The servo rotates the ultrasonic sensor to scan different directions.<br>
       The car turns to a clear direction, or backs up and turns if all scanned directions are blocked.
     </div>
     <img src="_static/V32.png" alt="obstacle lesson" style="max-width:100%; height:auto; margin-top:0px;margin-bottom:20px;">

     <div class="text-orange">How to use</div>
     <div class="text-blue">
      <span style="color: #ec4d08ff; font-weight: 700;">Code location:</span> <span style="display: inline-block; color: #bb901aff; font-weight: 700; background: #fff4e8; border: 1px solid #f3cfaa; border-radius: 8px; padding: 2px 8px;">Lesson_Code/SmartRobotCar_Obstacle/SmartRobotCar_Obstacle.ino</span><br>
      <span style="color: #ec4d08ff; font-weight: 700;">Code upload method:</span> <a href="upload_arduino.html" style="color: #bb901aff; font-weight: 700; text-decoration: none; border-bottom: 2px solid #bb901aff;">Upload Program to Arduino UNO Board</a><br><br>

      1. Open <span style="color: #bb901aff; font-weight: 700;">"SmartRobotCar_Obstacle.ino"</span> in Arduino IDE.<br>
      2. Upload the code to the Arduino UNO board.<br>
      3. Place the robot car on the floor or a large table with obstacles in front of it.<br>
      4. Turn on the power.<br>
      5. Observe how the car detects and avoids the obstacles automatically.
     </div>

     <div class="text-orange">Tips</div>
     <div class="text-blue">
       Leave enough space for the robot car to turn.<br>
       Flat objects are easier for the ultrasonic sensor to detect than very thin or soft objects.<br>
       Make sure the servo and ultrasonic module are installed firmly before testing.
     </div>
   </div>

