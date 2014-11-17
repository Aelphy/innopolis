function WS_DISPLAY
    L1 = 3
    L2 = 1
    L3 = 1
    
    figure
    circle([0,0], L1+L2+L3)
    
    if L1 - (L2 + L3) >= 0
        hold on
        circle([0,0], L1 - (L2 + L3))
        hold off
    else
        figure
        circle([0,0], (L2 + L3) - L1)
    end
end