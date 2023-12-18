
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity RobotFSM_tb is
end RobotFSM_tb;

architecture Behavioral of RobotFSM_tb is
    -- Declare signals for testbench
    signal clk : STD_LOGIC := '0';
    signal reset : STD_LOGIC := '0';
    signal objForward : STD_LOGIC := '0';
    signal objLeft : STD_LOGIC := '0';
    signal objRight : STD_LOGIC := '0';
    signal turn_right : STD_LOGIC;
    signal turn_left : STD_LOGIC;
    signal go_forward : STD_LOGIC;

    -- Instantiate the RobotFSM module
    component RobotFSM
        Port ( 
            clk : in STD_LOGIC;
            reset : in STD_LOGIC;
            objForward : in STD_LOGIC;
            objLeft : in STD_LOGIC;
            objRight : in STD_LOGIC;
            turn_right : out STD_LOGIC;
            turn_left : out STD_LOGIC;
            go_forward : out STD_LOGIC
        );
    end component;

begin
    -- Instantiate the RobotFSM module
    UUT : RobotFSM
        port map (
            clk => clk,
            reset => reset,
            objForward => objForward,
            objLeft => objLeft,
            objRight => objRight,
            turn_right => turn_right,
            turn_left => turn_left,
            go_forward => go_forward
        );

    -- Clock process for simulation
    process
    begin
        clk <= '0';
        wait for 5 ns;  -- Adjust the time based on your design
        clk <= '1';
        wait for 5 ns;
    end process;

    -- Stimulus process
    process
    begin
        reset <= '1';
        wait for 10 ns;  -- Wait for a few clock cycles after reset
        reset <= '0';

        -- Test case 1: Move forward
        objForward <= '1';
        wait for 20 ns;

        -- Test case 2: Obstacle detected
        objForward <= '0';
        objLeft <= '0';
        objRight <= '0';
        wait for 20 ns;

        -- Test case 3: Right turn
        objRight <= '1';
        wait for 20 ns;

        -- Add more test cases as needed

        -- End simulation
        wait;
    end process;

end Behavioral;
