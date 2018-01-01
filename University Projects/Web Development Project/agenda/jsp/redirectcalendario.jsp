<!--
Java Server Page che gestisce la selezione del giorno,mese e anno selezionati dalle combobox presenti
nella pagina calendario.html
-->
<!DOCTYPE html>
<html>
  <head> 
  </head>
  <body>
  <%
    //pagina utilizzata per reuperare i dati dalle combobox contenute nella homepage in modo da ricostruire correttamente l'url in base alla data selezionata
    String anno=request.getParameter("Boxanno");
    String mese=request.getParameter("Boxmese");
    String giorno=request.getParameter("Boxgiorno");
    if(anno!="" && mese!="" && giorno!=""){  //se sono state lesezionate tutte le tre combobox allora ricostruisci l'url
      String redirectURL = "../static/calendario.html?anno="+anno+"&mese="+mese+"&giorno="+giorno;
      response.sendRedirect(redirectURL);
    }
    else{//altrimenti rimanda alla stessa pagina
      String redirectURL = "../static/calendario.html";
      response.sendRedirect(redirectURL);
    }
  %>
  </body>
</html>