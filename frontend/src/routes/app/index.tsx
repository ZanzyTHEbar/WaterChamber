import Header from "@components/Header";
import Home from "@pages/Home";
/* import Settings from "@pages/Settings"; */
import { BrowserRouter, Route, Routes } from "react-router-dom";

export default function AppRoutes() {
    return (
        <BrowserRouter basename={"/"}>
            <Header name="Water Chamber" />
            <Routes>
                <Route path="/" element={<Home />} />
                {/* <Route path="/settings" element={<Settings />} /> */}
            </Routes>
        </BrowserRouter>
    );
}
