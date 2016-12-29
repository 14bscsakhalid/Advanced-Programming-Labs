/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab11_server;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Anas
 */
public class Lab11_server {

    /**
     * @param args the command line arguments
     */
    
    public static void mergeFiles(List<File> files, File into) throws IOException {
    try (BufferedOutputStream mergingStream = new BufferedOutputStream(
            new FileOutputStream(into))) {
        for (File f : files) {
            Files.copy(f.toPath(), mergingStream);
        }
        System.out.println("Merged");
    }
}
    
    public static void main(String[] args) throws SocketException, IOException {
        // TODO code application logic here
        List recv = new ArrayList();
        DatagramSocket serverSocket = new DatagramSocket(5000);
            byte[] receiveData = new byte[1024];
            while(true)
               {
                  DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                  serverSocket.receive(receivePacket);
                  
                  String sentence = new String(receivePacket.getData());
                  if (sentence.equals("end")){
                      System.out.println("end is here");
                      break;
                  }else{
                      recv.add(receivePacket);
                  }
                  
                  System.out.println("received.");
               }
            
            mergeFiles(recv, (new File("F:\\work\\4th Semester\\Web Engineering\\lab11_server\\save.zip")));
            
        
    }
    
}
