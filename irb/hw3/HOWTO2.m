function out = HOWTO(ee_matrix)
    x = ee_matrix(1, 4)
    y = ee_matrix(2, 4)
    z = ee_matrix(3, 4)
    
    l2 = 1
    p = 1
    n = 1
    
    phi = asin(y/n)
    theta = 2 * atan(p + sqrt(p^2 - x^2 + (n * cos(phi) - l2)^2))
    l1 = l2 * sin(theta) - p * cos(theta) - n * sin(theta) * cos(phi) - z
    
    L1 = Link([0 -l1 0 0],'standard')
    L2 = Link([theta 0 l1 -pi/2],'standard')
    L3 = Link([phi p -l2 pi/2],'standard')
    L4 = Link([0 0 n 0],'standard')
    
    out = [theta, phi, l1]

    robot = SerialLink([L1 L2 L3 L4], 'name', 'robot');
    robot.plot([0, theta, phi, 0])
end