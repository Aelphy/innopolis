function out = HOWTO(ee_matrix)
    x = ee_matrix(1, 4)
    y = ee_matrix(2, 4)
    phi = acos(ee_matrix(1, 1))
    
    x1 = x - x * sin(phi)
    y1 = y - y * cos(phi)
    
    l1 = 1
    l2 = 1
    l3 = 1
    
    theta1 = acos((x1^2 + y1^2 - l1^2 - l2^2) / (2 * l1 * l2))
    theta2 = asin((l1^2 - l2^2 + x1^2 + y1^2) / (2 * l1 * sqrt(x1^2 + y1^2))) - atan(y1/x1)
    theta3 = phi - (theta1 + theta2)
    
    L1 = Link([theta1 0 0 0],'standard')
    L2 = Link([theta2 0 l1 0],'standard')
    L3 = Link([theta3 0 l2 0],'standard')
    L4 = Link([0 0 l3 0],'standard')
    
    out = [theta1, theta2, theta3]

    robot = SerialLink([L1 L2 L3 L4], 'name', 'robot');
    robot.plot([theta1, theta2, theta3, 0])
end