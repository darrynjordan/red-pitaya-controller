function [ fracNum ] = getFracNum( Vco )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

fracNum = ((2^24)*((Vco + 2400)/25 - 96));

end

