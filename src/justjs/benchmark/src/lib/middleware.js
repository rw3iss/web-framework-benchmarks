export default class Middleware {

    handleRequest(req, res, next) {
        next();
    }

}