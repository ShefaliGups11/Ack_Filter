#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/traffic-control-module.h"
//#include "ns3/flow-monitor-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("DumbbellTopology");


std::string dir = "Plots/";

static void
tracer (uint32_t oldval, uint32_t newval)
{
  std::ofstream fPlotQueue (dir + "cwndTraces/A.plotme", std::ios::out | std::ios::app);
  //fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/1446.0 << std::endl;
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/536.0 << std::endl;
  fPlotQueue.close ();
}

static void
tracer1 (uint32_t oldval, uint32_t newval)
{
  std::ofstream fPlotQueue (dir + "cwndTraces/B.plotme", std::ios::out | std::ios::app);
  //fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/1446.0 << std::endl;
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/536.0 << std::endl;
  fPlotQueue.close ();
}

static void
tracer2 (uint32_t oldval, uint32_t newval)
{
  std::ofstream fPlotQueue (dir + "cwndTraces/C.plotme", std::ios::out | std::ios::app);
  //fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/1446.0 << std::endl;
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/536.0 << std::endl;
  fPlotQueue.close ();

}

static void
tracer3 (uint32_t oldval, uint32_t newval)
{
  std::ofstream fPlotQueue (dir + "cwndTraces/D.plotme", std::ios::out | std::ios::app);
  //fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/1446.0 << std::endl;
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/536.0 << std::endl;
  fPlotQueue.close ();
}

static void
tracer4 (uint32_t oldval, uint32_t newval)
{
  std::ofstream fPlotQueue (dir + "cwndTraces/E.plotme", std::ios::out | std::ios::app);
  //fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/1446.0 << std::endl;
  fPlotQueue << Simulator::Now ().GetSeconds () << " " << newval/536.0 << std::endl;
  fPlotQueue.close ();
}

static void
cwnd ()
{
  std::cout << "cwnd" << std::endl;
  
  Config::ConnectWithoutContext ("/NodeList/0/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&tracer));

  //Config::ConnectWithoutContext ("/NodeList/0/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&tracer));
  Config::ConnectWithoutContext ("/NodeList/1/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&tracer1));
  Config::ConnectWithoutContext ("/NodeList/2/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&tracer2));
  Config::ConnectWithoutContext ("/NodeList/3/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&tracer3));
  Config::ConnectWithoutContext ("/NodeList/4/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&tracer4));
}




int 
main (int argc, char  *argv[])
{
  char buffer[80];
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y-%I-%M-%S",timeinfo);
  std::string currentTime (buffer);

  CommandLine cmd;
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  NodeContainer nodes;
  nodes.Create (12);
 
  uint32_t meanPktSize = 500;
  uint32_t maxBytes = 0;
  //uint32_t MaxSize = 1000;
  std::string redLinkDataRate = "1Mbps";
  std::string redLinkDelay = "5ms";
  //std::string EcnMode ="NoEcn";
  std::string EcnMode ="ClassicEcn";
  bool useEcn = true;
  //bool enableFlowMonitor = true;
  // RED params
  NS_LOG_INFO ("Set RED params");
  Config::SetDefault ("ns3::RedQueueDisc::MaxSize", QueueSizeValue (QueueSize ("25p")));

  Config::SetDefault ("ns3::RedQueueDisc::MeanPktSize", UintegerValue (meanPktSize));
  Config::SetDefault ("ns3::RedQueueDisc::Wait", BooleanValue (true));
  Config::SetDefault ("ns3::RedQueueDisc::Gentle", BooleanValue (true));
  Config::SetDefault ("ns3::RedQueueDisc::QW", DoubleValue (0.002));
  Config::SetDefault ("ns3::RedQueueDisc::MinTh", DoubleValue (5));
  Config::SetDefault ("ns3::RedQueueDisc::MaxTh", DoubleValue (15));
  Config::SetDefault ("ns3::RedQueueDisc::UseEcn", BooleanValue (useEcn));
  Config::SetDefault ("ns3::TcpSocketBase::EcnMode", StringValue (EcnMode));



  PointToPointHelper pointToPoint, pointToPointRouter;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("500Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  pointToPointRouter.SetDeviceAttribute ("DataRate", StringValue ("1Mbps"));
  pointToPointRouter.SetChannelAttribute ("Delay", StringValue ("5ms"));

  NetDeviceContainer Devn0n5,Devn1n5,Devn2n5,Devn3n5,Devn4n5,Devn5n6,Devn6n7,Devn6n8,Devn6n9,Devn6n10,Devn6n11,Devn6n12;
  Devn0n5 = pointToPoint.Install (nodes.Get(0),nodes.Get(5));
  Devn1n5 = pointToPoint.Install (nodes.Get(1),nodes.Get(5));
  Devn2n5 = pointToPoint.Install (nodes.Get(2),nodes.Get(5));
  Devn3n5 = pointToPoint.Install (nodes.Get(3),nodes.Get(5));
  Devn4n5 = pointToPoint.Install (nodes.Get(4),nodes.Get(5));
  Devn5n6 = pointToPointRouter.Install (nodes.Get(5),nodes.Get(6));
  Devn6n7 = pointToPoint.Install (nodes.Get(6),nodes.Get(7));
  Devn6n8 = pointToPoint.Install (nodes.Get(6),nodes.Get(8));
  Devn6n9 = pointToPoint.Install (nodes.Get(6),nodes.Get(9));
  Devn6n10 = pointToPoint.Install (nodes.Get(6),nodes.Get(10));
  Devn6n11 = pointToPoint.Install (nodes.Get(6),nodes.Get(11));
  //Devn6n12 = pointToPoint.Install (nodes.Get(6),nodes.Get(12))


  InternetStackHelper stack;
  stack.Install (nodes);

  TrafficControlHelper tchRed;
  /*tchRed.SetRootQueueDisc ("ns3::RedQueueDisc", "LinkBandwidth", StringValue (redLinkDataRate),
                           "LinkDelay", StringValue (redLinkDelay));*/
  tchRed.SetRootQueueDisc ("ns3::FifoQueueDisc");
  //tchRed.AddPacketFilter("ns3::PacketFilter");
  //tchRed.SetRootQueueDisc ("ns3::RedQueueDisc");
  //tchRed.Uninstall(Devn5n6);
  QueueDiscContainer queueDiscs;
  queueDiscs = tchRed.Install (Devn5n6);



  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (Devn0n5);

  Ipv4AddressHelper address1;
  address.SetBase ("10.1.2.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces1 = address.Assign (Devn1n5);

  Ipv4AddressHelper address2;
  address.SetBase ("10.1.3.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces2 = address.Assign (Devn2n5);
  
  Ipv4AddressHelper address3;
  address.SetBase ("10.1.4.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces3 = address.Assign (Devn3n5);

  Ipv4AddressHelper address4;
  address.SetBase ("10.1.5.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces4 = address.Assign (Devn4n5);

  Ipv4AddressHelper address5;
  address.SetBase ("10.1.6.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces5 = address.Assign (Devn5n6);
  
  Ipv4AddressHelper address6;
  address.SetBase ("10.1.7.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces6 = address.Assign (Devn6n7);

  Ipv4AddressHelper address7;
  address.SetBase ("10.1.8.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces7 = address.Assign (Devn6n8);

  Ipv4AddressHelper address8;
  address.SetBase ("10.1.9.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces8 = address.Assign (Devn6n9);

  Ipv4AddressHelper address9;
  address.SetBase ("10.1.100.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces9 = address.Assign (Devn6n10);

  Ipv4AddressHelper address10;
  address.SetBase ("10.1.11.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces10 = address.Assign (Devn6n11);

 

  PacketSinkHelper sink("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),50000));
  ApplicationContainer sinkApp = sink.Install(nodes.Get(7));
  PacketSinkHelper sink1("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),50001));
  ApplicationContainer sinkApp1 = sink1.Install(nodes.Get(8));
  PacketSinkHelper sink2("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),50002));
  ApplicationContainer sinkApp2 = sink2.Install(nodes.Get(9));
  PacketSinkHelper sink3("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),50003));
  ApplicationContainer sinkApp3 = sink3.Install(nodes.Get(10));
  PacketSinkHelper sink4("ns3::TcpSocketFactory",InetSocketAddress(Ipv4Address::GetAny(),50004));
  ApplicationContainer sinkApp4 = sink4.Install(nodes.Get(11));


  BulkSendHelper source ("ns3::TcpSocketFactory",(InetSocketAddress(interfaces6.GetAddress(1),50000)));
  source.SetAttribute ("MaxBytes", UintegerValue (maxBytes));
  BulkSendHelper source1 ("ns3::TcpSocketFactory",(InetSocketAddress(interfaces7.GetAddress(1),50001)));
  source1.SetAttribute ("MaxBytes", UintegerValue (maxBytes));
  BulkSendHelper source2 ("ns3::TcpSocketFactory",(InetSocketAddress(interfaces8.GetAddress(1),50002)));
  source2.SetAttribute ("MaxBytes", UintegerValue (maxBytes));
  BulkSendHelper source3 ("ns3::TcpSocketFactory",(InetSocketAddress(interfaces9.GetAddress(1),50003)));
  source3.SetAttribute ("MaxBytes", UintegerValue (maxBytes));
  BulkSendHelper source4 ("ns3::TcpSocketFactory",(InetSocketAddress(interfaces10.GetAddress(1),50004)));
  source4.SetAttribute ("MaxBytes", UintegerValue (maxBytes));
  
  
  ApplicationContainer sourceApp = source.Install(nodes.Get(0));
  ApplicationContainer sourceApp1 = source1.Install(nodes.Get(1));
  ApplicationContainer sourceApp2 = source2.Install(nodes.Get(2));
  ApplicationContainer sourceApp3 = source3.Install(nodes.Get(3));
  ApplicationContainer sourceApp4 = source4.Install(nodes.Get(4));
      
   
   Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
   
  //pointToPoint.EnablePcapAll ("pcap",true);
  
  //node23.EnablePcapAll ();

  sourceApp.Start(Seconds(0.0));
  sourceApp.Stop(Seconds(100.0));
  sourceApp1.Start(Seconds(0.0));
  sourceApp1.Stop(Seconds(100.0));
  sourceApp2.Start(Seconds(0.0));
  sourceApp2.Stop(Seconds(100.0));
  sourceApp3.Start(Seconds(0.0));
  sourceApp3.Stop(Seconds(100.0));
  sourceApp4.Start(Seconds(0.0));
  sourceApp4.Stop(Seconds(100.0));


  sinkApp.Start(Seconds(0.0));
  sinkApp.Stop(Seconds(100.0));
  sinkApp1.Start(Seconds(0.0));
  sinkApp1.Stop(Seconds(100.0));
  sinkApp2.Start(Seconds(0.0));
  sinkApp2.Stop(Seconds(100.0));
  sinkApp3.Start(Seconds(0.0));
  sinkApp3.Stop(Seconds(100.0));
  sinkApp4.Start(Seconds(0.0));
  sinkApp4.Stop(Seconds(100.0));

  dir += (currentTime + "/");
  std::string dirToSave = "mkdir -p " + dir;
  system (dirToSave.c_str ());
  system ((dirToSave + "/pcap/").c_str ());
  system ((dirToSave + "/cwndTraces/").c_str ());
  system ((dirToSave + "/queueTraces/").c_str ());
  pointToPoint.EnablePcapAll (dir + "pcap/N", true);
  
  Simulator::Schedule (Seconds (0.1), &cwnd);

 

  Simulator::Stop(Seconds(100.0));
  Simulator::Run();

 

  QueueDisc::Stats st = queueDiscs.Get (0)->GetStats ();
  std::cout << st << std::endl;
  

  Simulator::Destroy();
  return 0;
}
