function out = HOWTO(ee_matrix)
    x = ee_matrix(1, 4)
    y = ee_matrix(2, 4)
    z = ee_matrix(3, 4)
    
    l = 1
    R2 = 1
    p = l + R2
    d = sqrt(x^2 + y^2 + z^2) - p
    phi = -asin(y*sqrt((x^2 + y^2 + z^2)/(x^2 + y^2))/(d + p))
    theta = asin(sqrt((x^2 + y^2)/(x^2 + y^2 + z^2)))
    
    L1 = Link([phi 0 0 0],'standard')
    L2 = Link([theta 0 0 -pi/2],'standard')
    L3 = Link([0 0 d 0],'standard')
    
    out = [d, phi, theta]

    robot = SerialLink([L1 L2 L3], 'name', 'robot');
    robot.plot([phi, theta, 0])
end