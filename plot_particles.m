
M = dlmread('particlesinfo.txt');
map = dlmread('map.txt').*100;


image(map);
hold on;
t=[];
for i=1:size(M,1)
    if(M(i,3)<0)
        t = [t;i];
    end
end
M(t,:) = [];
plot(M(:,1)+1,M(:,2)+1,'.w');

hold off;


