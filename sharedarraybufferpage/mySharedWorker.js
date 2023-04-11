// listen for main to transfer the buffer to myWorker
self.onmessage = function handleMessageFromMain(msg) {
    console.log("message from main received in worker:", msg);
  
    const bufTransferredFromMain = msg.data;
  
    console.log(
      "buf.byteLength in worker BEFORE post back to main:",
      bufTransferredFromMain.byteLength
    );
  
    // send buf back to main and transfer the underlying ArrayBuffer
    self.postMessage(bufTransferredFromMain);
  
    console.log(
      "buf.byteLength in worker AFTER post back to main:",
      bufTransferredFromMain.byteLength
    );
  };
  