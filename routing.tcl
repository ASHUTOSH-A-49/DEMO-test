#IMP***  -  install this first : sudo apt-get update && sudo apt-get install xgraph
#Create a simulator object
set ns [new Simulator]

#Open the output trace file where our crayon will get its colors
set f0 [open out0.tr w]

#Create 2 houses (nodes)
set n0 [$ns node]
set n1 [$ns node]

#Connect the houses with a road (duplex link)
$ns duplex-link $n0 $n1 1Mb 100ms DropTail

# ADDED FIX: We need a toy car factory (traffic) to send down the road!
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

# ADDED FIX: Attach the toy box (sink) to house n1 (not n4!)
set sink0 [new Agent/LossMonitor]
$ns attach-agent $n1 $sink0
$ns connect $udp0 $sink0

#Define a 'finish' procedure to pack up our toys
proc finish {} {
    global f0
    #Close the output files
    close $f0
    #Call xgraph to draw the picture!
    exec xgraph out0.tr -geometry 800x400
    exit 0
}

#Define a procedure which checks the speed every half second
proc record {} {
    global sink0 f0
    #Get an instance of the simulator
    set ns [Simulator instance]
    #Set the time after which we check the speed again
    set time 0.5
    #How many toy cars made it to the box?
    set bw0 [$sink0 set bytes_]
    #Get the current time
    set now [$ns now]
    #Calculate the speed and write it down for the magical crayon
    puts $f0 "$now [expr $bw0/$time*8/1000000]"
    #Reset the box back to zero for the next check (WITH THE SPACE!)
    $sink0 set bytes_ 0
    #Re-schedule the procedure
    $ns at [expr $now+$time] "record"
}

#Start logging the speed
$ns at 0.0 "record"

# ADDED FIX: Tell the toy cars to start and stop driving!
$ns at 0.1 "$cbr0 start"
$ns at 59.9 "$cbr0 stop"

#End the game at 60 seconds
$ns at 60.0 "finish"

#Run the simulation
$ns run