// SELVA GANAPATHY A/L MUTHU KUMAR
// YOGANATHAN SHUNMUGAM
// PAGITHEREN A/L UMABATHY
// NESHADRAJ A/L SASIDHARAN

simple WirelessHost
    {
         gates: 
             input in; 
             output out; 
      } 
             network Assignment2
             { @display("bgb=800,800");
                  
                      submodules: 
                          laptop1: WirelessHost 
                          { @display("p=100,100;i=device/laptop"); }
                           laptop2: WirelessHost 
                           { @display("p=400,100;i=device/laptop"); }
                            router: WirelessHost 
                            { @display("p=250,300;i=device/router"); }
                             connections: 
                                 laptop1.out --> { delay = 100ms; } --> router.in; 
                                 laptop2.in <-- { delay = 100ms; } <-- router.out; 
                                 laptop2.out --> { delay = 100ms; } --> laptop1.in; 
                                 }