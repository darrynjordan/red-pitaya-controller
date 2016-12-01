function [ time_delay ] = beatToTime( beat_freq, bandwidth, modulation_period )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

time_delay = (beat_freq*modulation_period)/bandwidth;

end

