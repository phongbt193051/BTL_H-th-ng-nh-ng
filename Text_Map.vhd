
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity RobotFSM is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           objForward : in STD_LOGIC;
           objLeft : in STD_LOGIC;
           objRight : in STD_LOGIC;
           turn_right : out STD_LOGIC;
           turn_left : out STD_LOGIC;
           go_forward : out STD_LOGIC
    );
end RobotFSM;

architecture Behavioral of RobotFSM is
    -- State definition
    type RobotState is (OBSTACLE_FREE, 
                        FORWARD_MOVEMENT, 
                        OBSTACLE_DETECTED, 
                        RIGHT_TURN, 
                        LEFT_TURN, 
                        FORWARD_AFTER_RIGHT_TURN, 
                        FORWARD_AFTER_LEFT_TURN);
                        
    -- Internal signals
    signal current_state, next_state : RobotState;

    -- Add signal for parityPosition
    signal parityPosition : INTEGER := 0;

begin
    process(clk, reset)
    begin
        if reset = '1' then
            current_state <= OBSTACLE_FREE;
            parityPosition <= 0;
        elsif rising_edge(clk) then
            current_state <= next_state;

            -- Update parityPosition based on your logic
            -- Example: If objRight is '1', increment parityPosition
            if objRight = '1' then
                parityPosition <= parityPosition + 1;
            end if;
        end if;
    end process;

    process(current_state, objForward, parityPosition, objRight)
    begin
        -- Default assignments
        turn_right <= '0';
        turn_left <= '0';
        go_forward <= '0';

        case current_state is
            when OBSTACLE_FREE =>
                if objForward = '1' then
                    next_state <= FORWARD_MOVEMENT;
                else
                    next_state <= OBSTACLE_DETECTED;
                end if;
                
            when FORWARD_MOVEMENT =>
                if objForward = '1' then
                    next_state <= FORWARD_MOVEMENT;
                else
                    if parityPosition mod 2 = 1 then
                        next_state <= RIGHT_TURN;
                    else
                        next_state <= LEFT_TURN;
                    end if;
                end if;

            when OBSTACLE_DETECTED =>
                if parityPosition mod 2 = 1 then
                    next_state <= RIGHT_TURN;
                else
                    next_state <= LEFT_TURN;
                end if;

            when RIGHT_TURN =>
                next_state <= FORWARD_AFTER_RIGHT_TURN;
                turn_right <= '1';

            when LEFT_TURN =>
                next_state <= FORWARD_AFTER_LEFT_TURN;
                turn_left <= '1';

            when FORWARD_AFTER_RIGHT_TURN =>
                next_state <= OBSTACLE_FREE;
                go_forward <= '1';

            when FORWARD_AFTER_LEFT_TURN =>
                next_state <= OBSTACLE_FREE;
                go_forward <= '1';

            when others =>
                next_state <= OBSTACLE_FREE;
        end case;
    end process;

end Behavioral;
