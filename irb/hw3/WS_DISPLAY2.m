function WS_DISPLAY
    L1_MAX = 10
    n = 1
    p = 1
    L2 = 5
    
    for phi = 0:pi/10:2*pi
        for theta = 0:pi/10:2*pi
            for L1 = 0:1:L1_MAX    
                X = n*cos(theta)*cos(phi) - L2*cos(phi) - p*sin(theta);
                Y = n*sin(phi);
                Z = - n*sin(theta)*cos(phi) + L2*sin(phi) - p*cos(theta) - L1;
                
                scatter3(X,Y,Z);
                
                hold on
            end
        end
    end
    
    hold off
end