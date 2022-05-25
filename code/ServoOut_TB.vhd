-----------------------------------------------------------------------------
-- Title           : Title
-----------------------------------------------------------------------------
-- Author          : Daniel Pelikan
-- Date Created    : 01-07-2016
-----------------------------------------------------------------------------
-- Description     : Description
--							
--
-----------------------------------------------------------------------------
-- Copyright 2016. All rights reserved
-----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use IEEE.numeric_std.all;


entity ServoOut_TB is 
end entity;

architecture TB of ServoOut_TB is
     constant clk_period : time := 20 ns;
	component ServoOut is
		port 
		(
			clk		: in std_logic;
			rst_n		: in std_logic;
			reg1		: in std_logic_vector(7 downto 0);
			ena_in	: in std_logic;
			gpio0		: out std_logic
			
		);
	end component;
 

	signal clk			: std_logic;
	signal rst_n		: std_logic;
	signal reg1		   : std_logic_vector(7 downto 0);
	signal gpio0			: std_logic;			

begin

	UUT: ServoOut 
		port map 
		(
			clk			=> clk,
			rst_n		=> rst_n,
			reg1		=> reg1,
			ena_in		=> '1',
			gpio0		=> gpio0			
		);
		  
     clk_process :process
     begin
          CLK <= '1';
          wait for clk_period/2;
          CLK <= '0';
          wait for clk_period/2;
     end process;
     rst_process :process
     begin
          rst_n <= '0';
          wait for clk_period/2;
          rst_n <= '1';
		  wait;		  
     end process;
	 
	 
	 
     stimulus : process
     begin
		reg1 <= "00000000";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
		reg1 <= "00000001";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
		reg1 <= "00000010";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
		reg1 <= "00000011";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
		reg1 <= "00000100";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
		reg1 <= "00000101";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
		reg1 <= "00001000";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
		reg1 <= "11111111";
		wait until gpio0 = '1';
		wait until gpio0 = '0';
		wait until gpio0 = '1';
     end process;		
end TB;
