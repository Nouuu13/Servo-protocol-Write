-----------------------------------------------------------------------------
-- Title           : Title
-----------------------------------------------------------------------------
-- Author          : Detrait Romain
-- Date Created    : 23/05/22
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


entity ServoOut is
	port 
	(
		clk		: in std_logic;
		rst_n		: in std_logic;
		reg1		: in std_logic_vector(7 downto 0);
		ena_in	: in std_logic;
		gpio0		: 	out std_logic
		
	);
end entity;

architecture RTL of ServoOut is
	
	type state_type is (s0,s1);
	signal state : state_type; 
	
begin
	
	
		process (clk,rst_n,ena_in,reg1)
			variable count : natural := 0;
			constant MIN : natural :=50000;
			constant MAX : natural :=20e6/20;
			constant k : natural :=196;
			variable var: natural := 0;
		
	begin
		if rst_n = '0' then
			count := 0;
			state <= s0;
			gpio0 <= '1';-- Output signal for the servomotor.
		elsif rising_edge(clk) then
			case state is
				when s0 =>
					count := 0;
					if ena_in = '1' then 
						gpio0 <= '1';
						state <= s1; 
					end if;
				when s1 =>
					count := count + 1; 
					if count >= MIN+k*to_integer(unsigned(reg1)) then
						gpio0 <= '0';
					end if;				
					if count >= MAX then
						count := 0;
						gpio0 <= '1';
						state <= s0;
					end if;
				when others =>
					count :=0;
					state <= s0;	
			end case;					
		end if;
	end process;
end RTL;
