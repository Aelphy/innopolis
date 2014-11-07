T = [45,10,25,90,60,0]

L1 = Link([T(1) 0 0 0],'standard')
L2 = Link([T(2) 0 -0.3 -pi/2],'standard')
L3 = Link([T(3) 0 1 0],'standard')
L4 = Link([T(4) 0.2 0 pi/2],'standard')
L5 = Link([T(5) 0 1.5 0],'standard')
L6 = Link([T(6) 0 0 -pi/2],'standard')

robot = SerialLink([L1 L2 L3 L4 L5 L6], 'name', 'robot');
robot.plot(T)
