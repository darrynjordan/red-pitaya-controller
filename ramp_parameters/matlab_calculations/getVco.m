function [ Vco ] = getVco( fracNum )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

Vco = 25.0*(96.0 + fracNum/((2.0)^(24.0))) - 2400.0;

end

