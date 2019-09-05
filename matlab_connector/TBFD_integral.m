classdef TBFD_integral
    properties
        table_order
        x_min
        x_max
        y_min
        y_max
        delta_x
        table_filepath
        
        x
        y
        
        builtin_orders = [0 -1];
        
    end
    
    
    
    
    methods
        
        % Constructor
        function obj = TBFD_integral(order, index_filepath)
            % order_list: a list of orders to be supported by this integral
            % index_filepath: file path toward the index
            
            if ismember(order, obj.builtin_orders)
                obj.table_order = order;
                
                fprintf('Order %i can be solved analytically. Switched to use analytical formula.\n', order)
                
                return
            end
            
            % load index file
            fid = fopen(index_filepath, 'r');
            
            if fid == -1
                error('Index file %s does not exist', index_filepath)
            end
            
            tline = fgetl(fid);
            while ischar(tline)
                opt_list = strsplit(tline, ' ');
                
                try
                    if order == str2double(opt_list{1})
                        obj.table_order = str2double(opt_list{1});
                        obj.x_min = str2double(opt_list{2});
                        obj.x_max = str2double(opt_list{3});
                        obj.delta_x = str2double(opt_list{6});
                        obj.table_filepath = opt_list{7};
                        
                        break
                    end
                catch
                    error('index.db formating issue at line: %s', tline)
                end
                
                tline=fgetl(fid);
            end
            fclose(fid);
            
            if isempty(obj.table_order)
                error('no table is found for order %d', order)
            end
            
            % load the table into object
            try
                obj.y = dlmread(obj.table_filepath);
                obj.x = linspace(obj.x_min, obj.x_max, length(obj.y));
                obj.y_min = obj.get(obj.x_min);
                obj.y_max = obj.get(obj.x_max);
                
            catch
                error('Error encountered loading table at %s', obj.table_filepath)
                
            end
            
            
            fprintf('Successfully loaded FD integral table for order %f\n', order)
            
        end
        
        
        function result = get(obj, input_x)
            % Get the Fermi Dirac integral
            [sorted_input_x, sorted_index] = sort(input_x, 'ascend');
            [~, reverse_index] = sort(sorted_index);
            
            result_1 = exp(sorted_input_x(sorted_input_x < obj.x_min));
            result_2 = [];
            result_3 = [];
            
            switch obj.table_order
                case -0.5
                    result_2 = interp1(obj.x, obj.y, sorted_input_x((sorted_input_x >= obj.x_min) & (sorted_input_x <= obj.x_max)));
                    result_3 = 2.*sqrt(sorted_input_x(sorted_input_x > obj.x_max))./sqrt(pi);
                    
                case 0.5
                    result_2 = interp1(obj.x, obj.y, sorted_input_x((sorted_input_x >= obj.x_min) & (sorted_input_x <= obj.x_max)));
                    result_3 = 4.*input_x.^1.5./3./sqrt(pi);
                    
                case 1
                    result_2 = interp1(obj.x, obj.y, sorted_input_x((sorted_input_x >= obj.x_min) & (sorted_input_x <= obj.x_max)));
                    result_3 = 0.5.*input_x.^2;
                    
                    
                case 1.5
                    result_2 = interp1(obj.x, obj.y, sorted_input_x((sorted_input_x >= obj.x_min) & (sorted_input_x <= obj.x_max)));
                    result_3 = 8.*input_x.^2.5./15./sqrt(pi);
                    
                case 2
                    result_2 = interp1(obj.x, obj.y, sorted_input_x((sorted_input_x >= obj.x_min) & (sorted_input_x <= obj.x_max)));
                    result_3 = input_x.^3./6;
                    
            end
            
            result = [result_1, result_2, result_3];
            result = result(reverse_index);
        end
        
        
        
        
        
        
        
        function result = get_inverse(obj, input_y)
            % Get the Fermi Dirac integral
            [sorted_input_y, sorted_index] = sort(input_y, 'ascend');
            [~, reverse_index] = sort(sorted_index);
            
            result_1 = log(sorted_input_y(sorted_input_y < obj.y_min));
            result_2 = [];
            result_3 = [];
            
            
            switch obj.table_order
                case -0.5
                    result_2 = interp1(obj.y, obj.x, sorted_input_y((sorted_input_y > obj.y_min) & (sorted_input_y < obj.y_max)));
                    result_3 = pi./4.*sorted_input_y(sorted_input_y < obj.y_max).^2;
                    
                case 0.5
                    result_2 = interp1(obj.y, obj.x, sorted_input_y((sorted_input_y > obj.y_min) & (sorted_input_y < obj.y_max)));
                    result_3 = (3.*sqrt(pi).*sorted_input_y(sorted_input_y > obj.y_max)./4).^(1/1.5);
                    
                case 1
                    result_2 = interp1(obj.y, obj.x, sorted_input_y((sorted_input_y > obj.y_min) & (sorted_input_y < obj.y_max)));
                    result_3 = sqrt(2.*sorted_input_y(sorted_input_y > obj.y_max));
                    
                    
                case 1.5
                    result_2 = interp1(obj.y, obj.x, sorted_input_y((sorted_input_y > obj.y_min) & (sorted_input_y < obj.y_max)));
                    result_3 = (15.*sorted_input_y(sorted_input_y > obj.y_max)./8./sqrt(pi)).^(1/2.5);
                    
                    
                case 2
                    result_2 = interp1(obj.y, obj.x, sorted_input_y((sorted_input_y > obj.y_min) & (sorted_input_y < obj.y_max)));
                    result_3 = (6.*sorted_input_y(sorted_input_y > obj.y_max)).^(1/3);
                    
            end
            
            result = [result_1, result_2, result_3];
            result = result(reverse_index);
            
        end
    end
    
    
    
end