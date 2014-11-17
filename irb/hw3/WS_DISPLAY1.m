function WS_DISPLAY
    D_MAX = 10
    L = 10
    R2 = 5
    
    for phi = 0:pi/10:pi
        for theta = 0:pi/10:pi
            for d = 0:1:D_MAX    
                X = -(L + d + R2)*cos(phi)*sin(theta);
                Y = -(L + d + R2)*sin(phi)*sin(theta);
                Z = -(L + d + R2)*cos(theta);
                
                scatter3(X,Y,Z);
                
                hold on
            end
        end
    end
    
    hold off
end