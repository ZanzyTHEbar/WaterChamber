import axios from "axios";
import { useEffect, useState } from "react";

export default function useData(url) {
    const [isLoading, setIsLoading] = useState(true);
    const [data, setData] = useState(null);
    const [error, setError] = useState(false);

    useEffect(() => {
        const CancelToken = axios.CancelToken;
        let cancel;

        setIsLoading(true);
        setData(null);
        setError(false);

        axios.get(url, {
            cancelToken: new CancelToken((c) => (cancel = c))
        })
            .then((res) => {
                if (!res.data.data) {
                    setError('Failed to load data.');
                    return;
                }
                setData(res.data.data);
                setIsLoading(false);
            })
            .catch((err) => {
                if (axios.isCancel(err)) return;
                setError('Failed to load data.');
            });

        return () => cancel();
    }, [url]);

    return { isLoading, error, data };
}