<!-- 
Funzione che gestisce la creazione e l'invio di una e-mail ad una serie di contatti tramite 
un indirizzo di posta creato appositamente per lo scopo.
La funzione accetta in ingresso una stringa contenente gli indirizzi E-mail a cui inviare
il messaggio (stringa del formato "indirizzo1,indirizzo2,...,indirizzon"),una stringa contenente
l'oggetto del messaggio e una stringa contenente il corpo del mesaggio.
-->

<%@ page import="java.io.*,java.util.*,javax.mail.*" %>
<%@ page import="javax.mail.internet.*,javax.activation.*" %>
<%@ page import="javax.servlet.http.*,javax.servlet.*" %>
<%@ page import="java.util.Date"%>

<%!
public boolean sendMail(String to,String subject,String messaggio){
  boolean res=true;
  try{
    Properties props = new Properties();
    
    props.setProperty("mail.transport.protocol", "smtp"); //impostazione protocollo di trasmissione
    props.setProperty("mail.host","smtp.gmail.com");  //impostazione indirizzo server gmail	
    props.put("mail.smtp.auth", "true"); //il server richiede autenticazione per inviare mail
    props.put("mail.smtp.port", "465"); 	//porta di comunicazione con il server
    props.put("mail.smtp.socketFactory.port", "465");  //inpostiamo la porta a cui connettersi di default
    props.put("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory"); //specifica il nome della classe che implementa l'interfaccia javax.net.
										    //SocketFactory,classe usata per creare una connessione stmp
    props.put("mail.smtp.socketFactory.fallback", "false"); 	//impedisci di creare il socket con la classe standard di sistema nel caso in cui fallisca la creazione con libreria di google
    props.setProperty("mail.smtp.quitwait", "false"); 
    //creazione della sessione con il server tramite nome utente e password
    Session session = Session.getInstance(props,new javax.mail.Authenticator() { 
      protected PasswordAuthentication getPasswordAuthentication() { 
	return new PasswordAuthentication("staffagenda2012@gmail.com","tecweb2012"); 
      } 
    });
    //creazione di un messaggio
    MimeMessage message = new MimeMessage(session); 
    message.setSender(new InternetAddress("staffagenda2012@gmail.com")); //impostazione del mittente
    message.setSubject(subject); //impostazione dell'oggetto del messaggio
    message.setContent(messaggio, "text/plain"); //scrittura del corpo del messaggio
    if (to.indexOf(',') > 0) //Imposta i destinatari della mail contenuti nella stringa "to"
        message.setRecipients(Message.RecipientType.TO, InternetAddress.parse(to)); 
    else 
        message.setRecipient(Message.RecipientType.TO, new InternetAddress(to)); 
    //invio del messaggio
    Transport.send(message); 
  }
  catch (MessagingException e) {
    System.out.println(e);
    res=false;
  }  
  return res;
}
    
%>