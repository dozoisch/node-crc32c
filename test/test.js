var crc32c = require('../bin/crc32c');

// Normal usage
console.log(crc32c.compute(new Buffer('hello\n')));

console.log(crc32c.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));

console.log(crc32c.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}'));

// Using the batcher
var Batcher = new crc32c.Batcher();
Batcher.openSocket();
console.log(Batcher.compute(new Buffer('hello\n')));
console.log(Batcher.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));
console.log(Batcher.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}'));
Batcher.closeSocket();


/**
 * N repetition testing
 */

//** Using a new socket each time
var testString = '{"web-app":{"servlet":[{"servlet-name":"exampleCDS","servlet-class":"org.example.cds.CDSServlet","init-param":{"configGlossary:installationAt":"A Superb City, SW","configGlossary:adminEmail":"example@example.org","configGlossary:poweredBy":"example","configGlossary:poweredByIcon":"/images/example.gif","configGlossary:staticPath":"/content/static","templateProcessorClass":"org.example.WysiwygTemplate","templateLoaderClass":"org.example.FilesTemplateLoader","templatePath":"templates","templateOverridePath":"","defaultListTemplate":"listTemplate.htm","defaultFileTemplate":"articleTemplate.htm","useJSP":false,"jspListTemplate":"listTemplate.jsp","jspFileTemplate":"articleTemplate.jsp","cachePackageTagsTrack":200,"cachePackageTagsStore":200,"cachePackageTagsRefresh":60,"cacheTemplatesTrack":100,"cacheTemplatesStore":50,"cacheTemplatesRefresh":15,"cachePagesTrack":200,"cachePagesStore":100,"cachePagesRefresh":10,"cachePagesDirtyRead":10,"searchEngineListTemplate":"forSearchEnginesList.htm","searchEngineFileTemplate":"forSearchEngines.htm","searchEngineRobotsDb":"WEB-INF/robots.db","useDataStore":true,"dataStoreClass":"org.example.SqlDataStore","redirectionClass":"org.example.SqlRedirection","dataStoreName":"example","dataStoreDriver":"com.microsoft.jdbc.sqlserver.SQLServerDriver","dataStoreUrl":"jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon","dataStoreUser":"sa","dataStorePassword":"dataStoreTestQuery","dataStoreTestQuery":"SET NOCOUNT ON;select test=\'test\';","dataStoreLogFile":"/usr/local/tomcat/logs/datastore.log","dataStoreInitConns":10,"dataStoreMaxConns":100,"dataStoreConnUsageLimit":100,"dataStoreLogLevel":"debug","maxUrlLength":500}},{"servlet-name":"exampleEmail","servlet-class":"org.example.cds.EmailServlet","init-param":{"mailHost":"mail1","mailHostOverride":"mail2"}},{"servlet-name":"exampleAdmin","servlet-class":"org.example.cds.AdminServlet"},{"servlet-name":"fileServlet","servlet-class":"org.example.cds.FileServlet"},{"servlet-name":"exampleTools","servlet-class":"org.example.cms.exampleToolsServlet","init-param":{"templatePath":"toolstemplates/","log":1,"logLocation":"/usr/local/tomcat/logs/exampleTools.log","logMaxSize":"","dataLog":1,"dataLogLocation":"/usr/local/tomcat/logs/dataLog.log","dataLogMaxSize":"","removePageCache":"/content/admin/remove?cache=pages&id=","removeTemplateCache":"/content/admin/remove?cache=templates&id=","fileTransferFolder":"/usr/local/tomcat/webapps/content/fileTransferFolder","lookInContext":1,"adminGroupID":4,"betaServer":true}}],"servlet-mapping":{"exampleCDS":"/","exampleEmail":"/exampleutil/aemail/*","exampleAdmin":"/admin/*","fileServlet":"/static/*","exampleTools":"/tools/*"},"taglib":{"taglib-uri":"example.tld","taglib-location":"/WEB-INF/tlds/example.tld"}}}'

var fails = 0;
var error;
var N = 100000;
var label = 'Batch + new socket ' + N;

console.time(label);
for(var i = 0; i < N; ++i) {
    try {
        crc32c.compute(testString);
    } catch (err) {
        error = err;
        ++fails;
    }
}
console.timeEnd(label);

if (fails) {
    console.log(fails);
    console.log(error);
}


//** Using a single socket
fails = 0;
error = undefined;
// N is still defined
label = 'Batch + single socket ' + N;

console.time(label);
Batcher.openSocket();
for(var i = 0; i < N; ++i) {
    try {
        Batcher.compute(testString);
    } catch (err) {
        error = err;
        ++fails;
    }
}
Batcher.closeSocket();
console.timeEnd(label);

if (fails) {
    console.log(fails);
    console.log(error);
}
