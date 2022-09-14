*** Settings ***
Documentation   This is the integration test for the Toy Robot C++ program.
Library         Process
Library         String
Suite Setup     Check directory variables initialization



*** Test Cases ***
Program should be able to process optimal input file
    [Tags]   File   Normal input
    ${result} =   Run program with input file   optimal_file
    @{reports} =   Clean output and get report command results from console   ${result}
    Should Be Equal As Strings   ${reports}[0]   1,1,WEST   strip_spaces=True


Program should be able to process input file with blank lines
    [Tags]   File   Normal input
    ${result} =   Run program with input file   blank_lines_file
    @{reports} =   Clean output and get report command results from console   ${result}
    Should Be Equal As Strings   ${reports}[0]   3,1,WEST   strip_spaces=True


Program should be able to process input file with mixed casing lines
    [Tags]   File   Distorted input
    ${result} =   Run program with input file   mixed_casing_file
    @{reports} =   Clean output and get report command results from console   ${result}
    Should Be Equal As Strings   ${reports}[0]   1,4,EAST   strip_spaces=True


Program should be able to process input file with invalid command lines
    [Tags]   File   Distorted input
    ${result} =   Run program with input file   invalid_commands_file
    @{reports} =   Clean output and get report command results from console   ${result}
    Should Be Equal As Strings   ${reports}[0]   3,2,WEST   strip_spaces=True


Program should be able to process input file with multiple report lines
    [Tags]   File   Normal input
    ${result} =   Run program with input file   multiple_reports_file
    @{reports} =   Clean output and get report command results from console   ${result}
    Should Be Equal As Strings   ${reports}[0]   0,3,NORTH   strip_spaces=True
    Should Be Equal As Strings   ${reports}[1]   0,4,NORTH   strip_spaces=True
    Should Be Equal As Strings   ${reports}[2]   2,3,EAST   strip_spaces=True


Program should be able to process console input with optimal commands
    [Tags]   Console   Normal input
    ${result} =   Run program with console input   PLACE 1,3,NORTH\nLEFT\nLEFT\nLEFT\nMOVE\nMOVE\nREPORT
    @{reports} =   Clean output and get report command results from console   ${result.stdout}
    Should Be Equal As Strings   ${reports}[0]   3,3,EAST   strip_spaces=True


Program should be able to process console input with mixed casing commands
    [Tags]   Console   Distorted input
    ${result} =   Run program with console input   plACE 2,2,eASt\nmovE\nMOVe\nlEfT\nreporT
    @{reports} =   Clean output and get report command results from console   ${result.stdout}
    Should Be Equal As Strings   ${reports}[0]   4,2,NORTH   strip_spaces=True


Program should be able to process console input with invalid commands
    [Tags]   Console   Distorted input
    ${result} =   Run program with console input   Let's test this program\nmove\nright\nleft\nabove\nplace 0,0,north\nmove\oops invalid\nreport
    @{reports} =   Clean output and get report command results from console   ${result.stdout}
    Should Be Equal As Strings   ${reports}[0]   0,1,NORTH   strip_spaces=True


Program should be able to process console input with multiple report commands
    [Tags]   Console   Normal input
    ${result} =   Run program with console input   place 1,2,west\nright\nright\nmove\nmove\nreport\nleft\nmove\nmove\nmove\nreport\nleft\nmove\nmove\nleft\nmove\nreport
    @{reports} =   Clean output and get report command results from console   ${result.stdout}
    Should Be Equal As Strings   ${reports}[0]   3,2,EAST   strip_spaces=True
    Should Be Equal As Strings   ${reports}[1]   3,4,NORTH   strip_spaces=True
    Should Be Equal As Strings   ${reports}[2]   1,3,SOUTH   strip_spaces=True



*** Keywords ***
Check directory variables initialization
    ${release_dir_set} =   Run Keyword And Return Status   Variable Should Exist   ${RELEASE_DIR}
    Run Keyword If   not ${release_dir_set}   Fatal Error   Please pass the RELEASE_DIR variable when running this test!

    ${test_dir_set} =   Run Keyword And Return Status   Variable Should Exist   ${TEST_DIR}
    Run Keyword If   not ${test_dir_set}   Fatal Error   Please pass the TEST_DIR variable when running this test!


Run program with input file
    [Arguments]   ${input_file}
    ${result} =   Run Process   ${RELEASE_DIR}/toy_robot.exe   ${TEST_DIR}/test_input/${input_file}.txt
    [Return]   ${result.stdout}


Run program with console input
    [Documentation]   Argument is a string where commands are separated by \n (which simulates the ENTER key).
    [Arguments]   ${console_inputs}
    ${result} =   Run Process   D:/repos/toy-robot/build/Release/toy_robot.exe   stdin=${console_inputs}\n
    [Return]   ${result}


Clean output and get report command results from console
    [Arguments]   ${raw_cout}
    ${clean_cout} =   Replace String   ${raw_cout}   --- TOY ROBOT program (enter a blank command to exit) ---\n   ${EMPTY}
    ${clean_cout} =   Replace String   ${clean_cout}   Command for robot:   ${EMPTY}
    ${clean_cout} =   Replace String   ${clean_cout}   Robot status:   ${EMPTY}
    @{reports} =   Split String   ${clean_cout}   \n
    [Return]   @{reports}