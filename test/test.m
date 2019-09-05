% Test script for Table Based Fermi Dirac Integral connector
close all; clear; clc

%% Plot: Compare forward and inverse FD integral results
order_list = [-0.5 0.5 1 1.5 2];
colorpool = 'bgrcmyk';

% for index = 1:length(order_list)
%     order = order_list(index);
%     
%     tbfd_integral = TBFD_integral(order, '/home/wang159/Programs/FDIntegral_Table/table/index.db');
% 
%     x = linspace(-4,4,50);
%     y = tbfd_integral.get(x);
% 
%     semilogy(x,y,sprintf('-%s', colorpool(index)))
%     hold on
%     
%     inverse_x = tbfd_integral.get_inverse(y);
%     
%     semilogy(inverse_x, y, sprintf('o%s', colorpool(index)))
% 
% end
% 
% xlabel('\eta_F')
% ylabel('Fermi-Dirac Integral')
% 
% legend('-1/2','inverse -1/2', '1/2', 'inverse 1/2', '1' , 'inverse 1', '1.5', 'inverse 1.5','2', 'inverse 2')
% 
% grid minor
% 
% font_size = 12;
% set(gcf, 'color', 'white');
% set(gca, 'FontSize', font_size);
% set(get(gca,'title'), 'FontSize',font_size);
% set(get(gca,'xlabel'),'FontSize',font_size);
% set(get(gca,'ylabel'),'FontSize',font_size);
% 
% 
% %% Plot: Batch timing
% order = 0.5;
% size_list = logspace(1,8,30);
% colorpool = 'bgrcmyk';
% 
% forward_time = zeros(1, length(size_list));
% inverse_time = zeros(1, length(size_list));
% 
% for index = 1:length(size_list)
%     this_size = size_list(index);
%     
%     tbfd_integral = TBFD_integral(order, '/home/wang159/Programs/FDIntegral_Table/table/index.db');
% 
%     x = linspace(-4,4,this_size);
%     
%     tic
%     y = tbfd_integral.get(x);
%     forward_time(index) = toc;
%         
%     tic
%     inverse_x = tbfd_integral.get_inverse(y);
%     inverse_time(index) = toc;
%     
% end
% 
% figure
% 
% loglog(size_list, forward_time, '*g-')
% hold on
% loglog(size_list, inverse_time, '*r--')
% 
% xlabel('Size of batch')
% ylabel('Calculation time (s)')
% 
% legend('FD integral', 'inverse FD integral')
% 
% grid minor
% 
% font_size = 12;
% set(gcf, 'color', 'white');
% set(gca, 'FontSize', font_size);
% set(get(gca,'title'), 'FontSize',font_size);
% set(get(gca,'xlabel'),'FontSize',font_size);
% set(get(gca,'ylabel'),'FontSize',font_size);

%% Plot: Individual timing
order = 0.5;
call_list = logspace(1,5,30);
colorpool = 'bgrcmyk';

forward_time = zeros(1, length(call_list));
inverse_time = zeros(1, length(call_list));

for index = 1:length(call_list)
    this_call = call_list(index);
    
    tbfd_integral = TBFD_integral(order, '/home/wang159/Programs/FDIntegral_Table/table/index.db');
    
    tic
    for this_i = 1:this_call
        y = tbfd_integral.get(0);
    end
    forward_time(index) = toc;
    
    tic
    for this_i = 1:this_call
        inverse_x = tbfd_integral.get_inverse(1);
    end
    inverse_time(index) = toc;
    
end

figure

loglog(call_list, forward_time, '*k-')
hold on
loglog(call_list, inverse_time, '*b--')

xlabel('Number of function calls')
ylabel('Calculation time (s)')

legend('FD integral', 'inverse FD integral')

grid minor

font_size = 12;
set(gcf, 'color', 'white');
set(gca, 'FontSize', font_size);
set(get(gca,'title'), 'FontSize',font_size);
set(get(gca,'xlabel'),'FontSize',font_size);
set(get(gca,'ylabel'),'FontSize',font_size);

keyboard