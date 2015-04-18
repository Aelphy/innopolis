% bot = legoev3('usb');
% leftMotor = motor(bot, 'A');
% rightMotor = motor(bot, 'D');
% sonicMotor = motor(bot, 'B');
% sonic = sonicSensor(bot, 1);
% gyro = gyroSensor(bot, 4);
% touch = touchSensor(bot, 3);

PAUSE_DURATION = 0.050;

leftMotor.Speed = -30;
rightMotor.Speed = -30;
start(leftMotor);
start(rightMotor);

while (readTouch(touch) ~= 1)
    go_straight(leftMotor, rightMotor, 300, -30, PAUSE_DURATION, touch);
end

stop(leftMotor);
stop(rightMotor);
